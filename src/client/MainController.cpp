#include "MainController.h"

#include <nlohmann/json.hpp>

MainController::MainController()
{
    m_mainModel = new MainModel();
}

void MainController::processRequest(const std::string &serRequest)
{
    //    std::cout << serRequest << std::endl;
    json request(json::parse(serRequest));

    if (request["domain"] == toJsonString(Domain::AUTH)) {
        processAuth(serRequest);
    } else if (request["domain"] == toJsonString(Domain::RELATIONS)) {
        processRelations(serRequest);
    } else if (request["domain"] == toJsonString(Domain::CHAT)) {
        processChatBox(serRequest);
    } else if (request["domain"] == toJsonString(Domain::RESOURCE_REQUEST)) {
        processResourceRequest(serRequest);
    } else if (request["domain"] == toJsonString(Domain::IN_GAME_RELATED)) {
        processGameAction(serRequest);
    } else if (request["domain"] == toJsonString(Domain::GAME_SETUP)) {
        processGameSetup(serRequest);
    }
}

void MainController::processResourceRequest(const std::string &serRequest)
{
    json request = json::parse(serRequest);

    if (request.at("data_type") == toJsonString(DataType::LEADERBOARD)) {
        std::vector<std::pair<std::string, float>> leaderboard;
        for (auto &leader : request.at("serialized_data"))
            leaderboard.emplace_back(leader.at("username"), leader.at("elo"));
        m_mainModel->setLeaderboard(leaderboard);
    } else if (request.at("data_type") == toJsonString(DataType::FRIENDS_LIST)) {
        std::vector<std::string> friendsList;
        for (const auto &userFriend : request.at("serialized_data")) {
            friendsList.push_back(userFriend.get<std::string>());
        }
        if (friendsList.empty()) {
            m_mainModel->setFriendList({"No friend"});
            m_mainModel->setHasFriends(false);
        } else {
            m_mainModel->setFriendList(friendsList);
            m_mainModel->setHasFriends(true);
        }
    } else if (request.at("data_type") == toJsonString(DataType::GAME_CONFIG)) {
        std::cout << "Game config received" << std::endl;
    } else if (request.at("data_type") == toJsonString(DataType::FRIEND_REQUESTS_SENT)) {
        std::vector<std::string> friendRequestsSent;
        for (const auto &userFriend : request.at("serialized_data"))
            friendRequestsSent.push_back(userFriend.get<std::string>());
        m_mainModel->setFriendRequestsSent(friendRequestsSent);
    } else if (request.at("data_type") == toJsonString(DataType::FRIEND_REQUESTS_RECEIVED)) {
        std::vector<std::string> friendRequestsReceived;
        for (const auto &userFriend : request.at("serialized_data"))
            friendRequestsReceived.push_back(userFriend.get<std::string>());
        m_mainModel->setFriendRequestsReceived(friendRequestsReceived);
    } else if (request.at("data_type") == toJsonString(DataType::GAME_IDS)) {
        std::map<int, std::vector<std::string>> gameIds;
        for (auto &game : request.at("serialized_data")) {
            auto config = game.at("config");
            std::vector<std::string> players;
            for (auto &player : config.at("players"))
                players.push_back(player["username"].get<std::string>());
            gameIds[game.at("game_id").get<int>()] = players;
        }
        m_mainModel->setGameIds(gameIds);
    } else if (request.at("data_type") == toJsonString(DataType::CHATS)) {
        auto data = request.at("serialized_data");
        auto friendUsername = data.at("friend").get<std::string>();
        m_mainModel->clearFriendMessages(friendUsername);
        for (auto &chat : data.at("chats")) {
            auto sender = chat[0].get<std::string>();
            auto message = chat[1].get<std::string>();
            Message msg {sender, message};
            m_mainModel->addFriendMessage(friendUsername, msg);
        }
    } else if (request.at("data_type") == toJsonString(DataType::ELO)) {
        float elo = request.at("serialized_data").get<float>();
        m_mainModel->setElo(elo);
    }
}

void MainController::processAuth(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(ClientAuthAction::LOGIN)) {
        if (request.at("status") == toJsonString(RequestStatus::SUCCESS)) {
            m_mainModel->loginSuccessful(request.at("username"));
        } else if (request.at("status") == toJsonString(RequestStatus::FAILURE)) {
            m_mainModel->loginNotSuccessful();
        }
    }
}

void MainController::processRelations(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(FriendAction::FRIEND_REMOVE)) {
        m_mainModel->removeFriend(request.at("friend_rm_sender"));
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_ACCEPT)) {
        m_mainModel->acceptFriendRequest(request.at("friend_req_receiver"));
        m_mainModel->setHasFriends(true);
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_REQUEST)) {
        m_mainModel->addFriendRequestReceived(request.at("friend_req_sender"));
        m_mainModel->setFriendNotification(true);
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_REFUSE)) {
        m_mainModel->refuseFriendRequest(request.at("friend_req_receiver"));
    }
}

void MainController::processChatBox(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(ChatInteraction::FRIEND_MESSAGE)) {
        Message msg {request.at("sender"), request.at("message")};
        m_mainModel->addFriendMessage(request.at("sender"), msg);
        m_mainModel->setFriendNotification(true);
    }
    if (request.at("action") == toJsonString(ChatInteraction::IN_GAME_MESSAGE)) {
        //        m_mainModel->addGameMessage(request.at("sender"), request.at("receivers").get<std::vector<std::string>>(), request.at("message"));
    }
}

void MainController::processGameSetup(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(GameSetup::CREATE_GAME)) {

        auto gameID = request.at("game_id").get<int>();
        auto players = request.at("receivers").get<std::vector<std::string>>();
        players.push_back(request.at("sender").get<std::string>());

        m_mainModel->addGameId(gameID, players);
        m_mainModel->setGameNotification(true);
    }
}

void MainController::processGameAction(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(GameAction::START_GAME)) {
        // set game model config with serializedData["configuration"]
        m_mainModel->loadGame(request.at("configuration").dump());
        // set game started to true in main model
        m_mainModel->setIsGameStarted(true);

    } else if (request.at("action") == toJsonString(GameAction::END_GAME)) {
        // m_mainModel->process

    } else if (request.at("action") == toJsonString(JsonPlayerAction::MOVE_PAWN) || request.at("action") == toJsonString(JsonPlayerAction::PLACE_WALL)) {
        m_mainModel->processGameAction(request.at("move").dump());
    }

    std::cerr << "MainController::processGameAction: after processing\n";
}

MainModel *MainController::getMainModel()
{
    return m_mainModel;
}
