#include <catch2/catch.hpp>

#include "src/client/GameModel.h"
#include "src/common/SerializableMessageFactory.h"
#include "src/common/SocketUser.h"
#include "src/server/Database.h"
#include "src/server/LandingPool.h"
#include "src/server/ServerUser.h"
#include "src/server/UserHandler.h"

#include <future>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sockpp/tcp_connector.h>

class TestConnector : public SocketUser
{
public:
    TestConnector(const std::string &address, int16_t port)
    {
        sockpp::tcp_connector connector;
        connector.connect(sockpp::inet_address(address, port));
        setSocket(std::move(connector));
    }

    auto disconnect() -> void
    {
        close();
    }

    ~TestConnector()
    {
        disconnect();
    }
};

class TestServer
{
public:
    UserHub userHub;
    LandingPool entryDoor;
    std::thread th;

    TestServer(in_port_t port)
        : userHub {}
        , entryDoor {port, userHub}
    {
        th = std::thread {&LandingPool::openToConnections, &entryDoor};
        th.detach();
    }

    ~TestServer()
    {
        entryDoor.close();
    }
};

std::string getAnswer(TestConnector &conn, const std::string &request)
{
    conn.send(request);
    auto ans {conn.receive()};
    return ans;
}

void createUser(TestConnector &conn, const std::string &name, const std::string &pass)
{
    auto req {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTRATION, name, pass).dump()};
    getAnswer(conn, req);
}

void logUser(TestConnector &conn, const std::string &name, const std::string &pass)
{
    auto req {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, name, pass).dump()};
    getAnswer(conn, req);
}

void createAndLogUser(TestConnector &conn, const std::string &name, const std::string &pass)
{
    createUser(conn, name, pass);
    logUser(conn, name, pass);
}

void makeFriends(TestConnector &a, const std::string &aName, TestConnector &b, const std::string &bName)
{
    auto reqFriendReq {SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, aName, bName).dump()};
    auto reqFriendAcc {SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, aName, bName).dump()};

    // Send friend request
    a.send(reqFriendReq);
    auto reqRecv {b.receive()};

    // Receive friend request
    b.send(reqFriendAcc);
    auto accRecv {a.receive()};
}

void endGame(std::vector<TestConnector *> players)
{
    for (auto i = 0; i < players.size() - 1; ++i) {
        players[i]->disconnect();
        for (auto j = i + 1; j < players.size(); ++j) {
            players[j]->receive();
        }
    }
}

// Server
TestServer serv {12345};

SCENARIO("Authentification")
{
    DatabaseHandler::deleteAccount("foo");
    TestConnector test {"localhost", 12345};

    GIVEN("Registration")
    {
        THEN("Unique credentials should be successful")
        {
            auto req {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTRATION, "foo", "12345").dump()};

            auto ansSuccess {getAnswer(test, req)};
            auto expAnsSuccess {
                SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::REGISTRATION, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT, "foo")
                    .dump()};

            REQUIRE(ansSuccess == expAnsSuccess);

            THEN("Non unique credentials should not be successful")
            {
                auto ansFail {getAnswer(test, req)};
                auto expAnsFail {SerializableMessageFactory::serializeServerAnswer(
                    ClientAuthAction::REGISTRATION, RequestStatus::FAILURE, ServerAuthReturn::REGISTER_USERNAME_IN_USE, "foo")
                                     .dump()};
                REQUIRE(ansFail == expAnsFail);
            }

            GIVEN("Login")
            {

                THEN("Correct credentials for login should be successful")
                {
                    auto reqLogSuccess {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, "foo", "12345").dump()};
                    auto ansLogSuccess {getAnswer(test, reqLogSuccess)};
                    auto expAnsLogSuccess {
                        SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::LOGIN, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT, "foo")
                            .dump()};
                    REQUIRE(ansLogSuccess == expAnsLogSuccess);
                }

                THEN("Incorrect credentials for login should not be successful")
                {
                    auto reqLogFail {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, "foo", "54321").dump()};
                    auto ansLogFail {getAnswer(test, reqLogFail)};
                    auto expAnsLogFail {SerializableMessageFactory::serializeServerAnswer(
                        ClientAuthAction::LOGIN, RequestStatus::FAILURE, ServerAuthReturn::LOGIN_INCORRECT_USERNAME, "foo")
                                            .dump()};

                    REQUIRE(ansLogFail == expAnsLogFail);
                }
            }
        }
    }
}

SCENARIO("Resources exchange")
{
    DatabaseHandler::deleteAccount("foo");

    TestConnector foo {"localhost", 12345};

    // The creation and the log in are done in two steps because the elo
    // is cached on the server and is updated on certain occasions, including
    // the log in. Setting the elo in the DB after the login, results in
    // incorrect data because not updated on the server (only in the DB).
    GIVEN("ELO")
    {
        createUser(foo, "foo", "12345");

        DatabaseHandler::setELO("foo", 666);
        REQUIRE(DatabaseHandler::getELO("foo") == 666);

        logUser(foo, "foo", "12345");

        auto eloReq {SerializableMessageFactory::serializeRequestExchange(DataType::ELO).dump()};
        auto eloAns {getAnswer(foo, eloReq)};
        auto elo {getResourceFromAnswer<int>(eloAns)};

        REQUIRE(elo == 666);
    }

    GIVEN("Leaderboard")
    {
        createAndLogUser(foo, "foo", "12345");

        DatabaseHandler::setELO("foo", 666);
        REQUIRE(DatabaseHandler::getELO("foo") == 666);

        auto leadReq {SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD).dump()};
        auto leadAns {getAnswer(foo, leadReq)};
    }

    sleep(1);
}

SCENARIO("Relations")
{
    DatabaseHandler::deleteAccount("foo");
    DatabaseHandler::deleteAccount("bar");

    TestConnector foo {"localhost", 12345};
    TestConnector bar {"localhost", 12345};

    createAndLogUser(foo, "foo", "12345");
    createAndLogUser(bar, "bar", "12345");

    REQUIRE(serv.userHub.connectedUsers() == 2);
    REQUIRE(serv.userHub.namesOfConnectedUsers() == std::vector<std::string> {"foo", "bar"});

    GIVEN("Friends")
    {
        auto reqFriendReq {SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "foo", "bar").dump()};
        auto reqFriendAcc {SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, "foo", "bar").dump()};

        // Send friend request
        foo.send(reqFriendReq);
        auto reqRecv {bar.receive()};

        REQUIRE(serv.userHub.connectedUsers() == 2);
        REQUIRE(serv.userHub.namesOfConnectedUsers() == std::vector<std::string> {"foo", "bar"});

        // Receive friend request
        bar.send(reqFriendAcc);
        auto accRecv {foo.receive()};

        REQUIRE(reqFriendReq == reqRecv);
        REQUIRE(reqFriendAcc == accRecv);

        auto resReq {SerializableMessageFactory::serializeRequestExchange(DataType::FRIENDS_LIST).dump()};

        // Get updated friend lists
        auto fooFriends {getAnswer(foo, resReq)};
        auto barFriends {getAnswer(bar, resReq)};

        auto fooVec = getResourceFromAnswer<std::vector<std::string>>(fooFriends);
        auto barVec = getResourceFromAnswer<std::vector<std::string>>(barFriends);

        REQUIRE(fooVec == std::vector<std::string> {"bar"});
        REQUIRE(barVec == std::vector<std::string> {"foo"});
    }

    sleep(1);
}

SCENARIO("GameSetup")
{
    DatabaseHandler::deleteAccount("foo");
    DatabaseHandler::deleteAccount("bar");

    TestConnector foo {"localhost", 12345};
    TestConnector bar {"localhost", 12345};

    createAndLogUser(foo, "foo", "12345");
    createAndLogUser(bar, "bar", "12345");

    makeFriends(foo, "foo", bar, "bar");

    GIVEN("Game creation")
    {
        auto sender {"foo"};
        auto receivers {std::vector<std::string> {"bar"}};
        auto config = GameModel {std::vector<std::string> {"foo", "bar"}}.serialized();
        auto gameCreatReq {SerializableMessageFactory::serializeGameCreationRequest(sender, receivers, config).dump()};

        foo.send(gameCreatReq);

        REQUIRE(foo.receive() == bar.receive());

        auto gameIDReqfoo {SerializableMessageFactory::serializeRequestExchange(DataType::GAME_IDS).dump()};
        auto gameIDResfoo {getAnswer(foo, gameIDReqfoo)};

        auto gameIDReqbar {SerializableMessageFactory::serializeRequestExchange(DataType::GAME_IDS).dump()};
        auto gameIDResbar {getAnswer(bar, gameIDReqbar)};

        REQUIRE(gameIDResfoo == gameIDResbar);

        auto gameID {json::parse(gameIDResfoo)["serialized_data"][0]["game_id"].get<int>()};

        GIVEN("Join created game")
        {
            auto joinReqfoo {SerializableMessageFactory::serializeGameParticipationRequest(GameSetup::JOIN_GAME, gameID, "foo").dump()};
            auto quitReqfoo {SerializableMessageFactory::serializeGameParticipationRequest(GameSetup::QUIT_GAME, gameID, "foo").dump()};

            auto joinReqbar {SerializableMessageFactory::serializeGameParticipationRequest(GameSetup::JOIN_GAME, gameID, "bar").dump()};

            foo.send(joinReqfoo);
            foo.send(quitReqfoo);

            foo.send(joinReqfoo);
            bar.send(joinReqbar);

            auto gameStartfoo {foo.receive()};
            auto gameStartbar {bar.receive()};

            REQUIRE(gameStartfoo == gameStartbar);

            auto gameModel = GameModel {json::parse(gameStartfoo)["configuration"].dump()};

            GIVEN("Player actions")
            {
                gameModel.debugPrintBoard();

                auto action = gameModel.getPlayerAction(Point {4, 7});
                auto playerID = *gameModel.getCurrentPlayer();
                auto req = SerializableMessageFactory::serializePawnAction(action, playerID).dump();

                foo.send(req);
                auto ans = bar.receive();

                gameModel.processAction(json::parse(ans)["move"].dump());
                gameModel.debugPrintBoard();

                endGame(std::vector<TestConnector *> {&foo, &bar});
            }

            GIVEN("Wall actions")
            {
                gameModel.debugPrintBoard();

                auto action = gameModel.getWallAction(Point {0, 0}, WallOrientation::Horizontal);
                auto playerID = *gameModel.getCurrentPlayer();
                auto req = SerializableMessageFactory::serializeWallAction(action, playerID).dump();

                foo.send(req);
                auto ans = bar.receive();

                gameModel.processAction(json::parse(ans)["move"].dump());
                gameModel.debugPrintBoard();

                endGame(std::vector<TestConnector *> {&foo, &bar});
            }

            GIVEN("Surrender by request")
            {
                auto surrReqfoo = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::SURRENDER, "foo");
                foo.send(surrReqfoo.dump());

                /* auto expEndGame {GameRelatedActionsSerializableMessageFactory::serializeGameEnded(gameID).dump()}; */
                auto endGame {bar.receive()};

                surrReqfoo["sender"] = "foo";

                REQUIRE(endGame == surrReqfoo.dump());

                REQUIRE(DatabaseHandler::getPlayerGameIds("foo").empty());
                REQUIRE(DatabaseHandler::getPlayerGameIds("bar").empty());
            }

            GIVEN("Surrender by disconnect")
            {
                auto surrReqfoo = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::SURRENDER, "foo");
                foo.disconnect();

                /* auto expEndGame {GameRelatedActionsSerializableMessageFactory::serializeGameEnded(gameID).dump()}; */
                auto endGame {bar.receive()};

                surrReqfoo["sender"] = "foo";

                REQUIRE(endGame == surrReqfoo.dump());
            }
        }
    }

    foo.disconnect();
    bar.disconnect();

    sleep(1);
}

/* TODO: find a way to make it work */
/* SCENARIO("Sync and async requests") */
/* { */
/*     DatabaseHandler::deleteAccount("foo"); */
/*     DatabaseHandler::deleteAccount("bar"); */

/*     TestConnector foo {"localhost", 12345}; */
/*     TestConnector bar {"localhost", 12345}; */

/*     createAndLogUser(foo, "foo", "12345"); */
/*     createAndLogUser(bar, "bar", "12345"); */

/*     GIVEN("A sync request") */
/*     { */
/*         auto leadReq {SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD).dump()}; */
/*         auto frndReq {SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "bar", "foo").dump()}; */

/*         bar.send(frndReq); */
/*         sleep(1); */

/*         std::future<std::string> leadAns = std::async(getAnswer, foo, leadReq); */
/*         auto frndAns {foo.receive()}; */
/*     } */

/*     sleep(1); */
/* } */
