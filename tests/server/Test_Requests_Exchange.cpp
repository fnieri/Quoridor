#include <catch2/catch.hpp>

#include "src/common/SerializableMessageFactory.h"
#include "src/common/SocketUser.h"
#include "src/server/Database.h"
#include "src/server/LandingPool.h"
#include "src/server/ServerUser.h"
#include "src/server/UserHandler.h"

#include <iostream>
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

    ~TestConnector()
    {
        close();
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

/* template <typename T> */
/* T dataFromSerialized(const std::string &serRequest) */
/* { */
/*     json request(json::parse(serRequest)); */
/*     json jsonData = request["serialized_data"]; */
/*     T data = jsonData[0].get<T>(); */

/*     return data; */
/* } */

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
                SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::REGISTRATION, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT).dump()};

            REQUIRE(ansSuccess == expAnsSuccess);

            THEN("Non unique credentials should not be successful")
            {
                auto ansFail {getAnswer(test, req)};
                auto expAnsFail {SerializableMessageFactory::serializeServerAnswer(
                    ClientAuthAction::REGISTRATION, RequestStatus::FAILURE, ServerAuthReturn::REGISTER_USERNAME_IN_USE)
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
                        SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::LOGIN, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT).dump()};
                    REQUIRE(ansLogSuccess == expAnsLogSuccess);
                }

                THEN("Incorrect credentials for login should not be successful")
                {
                    auto reqLogFail {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, "foo", "54321").dump()};
                    auto ansLogFail {getAnswer(test, reqLogFail)};
                    auto expAnsLogFail {SerializableMessageFactory::serializeServerAnswer(
                        ClientAuthAction::LOGIN, RequestStatus::FAILURE, ServerAuthReturn::LOGIN_INCORRECT_USERNAME)
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
    createAndLogUser(foo, "foo", "12345");

    /* auto eloReq {SerializableMessageFactory::serializeRequestExchange(DataType::).dump()}; */
    /* auto resReq {SerializableMessageFactory::serializeRequestExchange(DataType::FRIENDS_LIST).dump()}; */
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

    sleep(1);
}
