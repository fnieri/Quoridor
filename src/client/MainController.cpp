#include "MainController.h"

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
        //        processGameAction(serRequest);
    } else if (request["domain"] == toJsonString(Domain::GAME_SETUP)) {
        processGameSetup(serRequest);
    }
}

void MainController::processResourceRequest(const std::string &serRequest)
{
    json request(json::parse(serRequest));

    if (request.at("data_type") == toJsonString(DataType::LEADERBOARD)) {
        std::vector<std::pair<std::string, float>> leaderboard;
        for (auto &leader: request.at("serialized_data"))
            leaderboard.emplace_back(leader.at("username"), leader.at("elo"));
        m_mainModel->setLeaderboard(leaderboard);
    } else if (request.at("data_type") == toJsonString(DataType::FRIENDS_LIST)) {
        std::vector<std::string> friendsList;
        for (const auto &userFriend : request.at("serialized_data")){
            friendsList.push_back(userFriend.get<std::string>());
        }
        m_mainModel->setFriendList(friendsList);
    } else if (request.at("data_type") == toJsonString(DataType::GAME_CONFIG)) {
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
        std::vector<int> gameIds;
        for (const auto &gameId : request.at("serialized_data"))
            gameIds.push_back(gameId.get<int>());
        m_mainModel->setGameIds(gameIds);
    } else if (request.at("data_type") == toJsonString(DataType::CHATS)) {
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
        m_mainModel->removeFriend(request.at("friend_rm_receiver"));
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_ACCEPT)) {
        m_mainModel->addFriend(request.at("friend_req_receiver"));
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_REQUEST)) {
        m_mainModel->addFriendRequestReceived(request.at("friend_req_sender"));
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_REFUSE)) {
        m_mainModel->refuseFriendRequest(request.at("friend_req_sender"));
    }
}

void MainController::processChatBox(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(ChatInteraction::FRIEND_MESSAGE)) {
        m_mainModel->addFriendMessage(request.at("sender"), request.at("message"));
    }
    if (request.at("action") == toJsonString(ChatInteraction::IN_GAME_MESSAGE)) {
        //        m_mainModel->addGameMessage(request.at("sender"), request.at("receivers").get<std::vector<std::string>>(), request.at("message"));
    }
}

void MainController::processGameSetup(const std::string &serRequest)
{
    //    json request(json::parse(serRequest));
    //    if (request.at("action") == toJsonString(GameSetup::CREATE_GAME)) {
    //     m_mainModel->loadGame();
    //    }
}

MainModel *MainController::getMainModel()
{
    return m_mainModel;
}