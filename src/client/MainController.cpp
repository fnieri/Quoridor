#include "MainController.h"

void MainController::processRequest(const std::string &serRequest)
{
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

    // FOR TESTING
    /// the "action" of a resource exchange is solely : "object_answer"
    if (request.at("action") == toJsonString(Exchange::OBJECT_ANSWER)) {
        if (request.at("data_type") == toJsonString(DataType::FRIENDS_LIST)) {
            std::vector<std::string> friendsList;
            for (auto userFriend : request.at("serialized_data"))
                friendsList.push_back(userFriend.get<std::string>());
            m_mainModel.setFriendList(friendsList);
        }
        else if (request.at("data_type") == toJsonString(DataType::LEADERBOARD)) {
            std::vector<std::pair<std::string, float>> leaderboard;
            for (auto it = request.at("serialized_data").begin(); it != request.at("serialized_data").end(); it++)
                leaderboard.push_back(std::pair<std::string, float>(it->at("username"), it->at("elo")));
            m_mainModel.setLeaderboard(leaderboard);
        }
    }



    /// these are never run because the 'action' of a Exchange is either 'object_answer' or 'object_request' or ....
    if (request.at("action") == toJsonString(DataType::LEADERBOARD)) {
        std::vector<std::pair<std::string, float>> leaderboard;
        for (auto it = request.at("serialized_data").begin(); it != request.at("serialized_data").end(); it++)
            leaderboard.push_back(std::pair<std::string, float>(request.at("username"), request.at("elo")));
        m_mainModel.setLeaderboard(leaderboard);
    } else if (request.at("action") == toJsonString(DataType::FRIENDS_LIST)) {
        std::vector<std::string> friendsList;
        for (auto userFriend : request.at("serialized_data"))
            friendsList.push_back(userFriend.get<std::string>());
        m_mainModel.setFriendList(friendsList);
        std::cout << request.at("serialized_data") << std::endl;
    } else if (request.at("action") == toJsonString(DataType::GAME_CONFIG)) {
        std::cout << request.at("serialized_data") << std::endl;
    } else if (request.at("action") == toJsonString(DataType::FRIEND_REQUESTS_SENT)) {
        std::cout << request.at("serialized_data") << std::endl;
    } else if (request.at("action") == toJsonString(DataType::FRIEND_REQUESTS_RECEIVED)) {
        std::cout << request.at("serialized_data") << std::endl;
    } else if (request.at("action") == toJsonString(DataType::GAME_IDS)) {
        std::cout << request.at("serialized_data") << std::endl;
    } else if (request.at("action") == toJsonString(DataType::CHATS)) {
        std::cout << request.at("serialized_data") << std::endl;
    } else if (request.at("action") == toJsonString(DataType::ELO)) {
        std::cout << request.at("serialized_data") << std::endl;
    }
}

void MainController::processAuth(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(ClientAuthAction::LOGIN)) {
        if (request.at("status") == toJsonString(RequestStatus::SUCCESS)) {
            m_mainModel.loginSuccessful(request.at("username"));
        } else if (request.at("status") == toJsonString(RequestStatus::FAILURE)) {
            m_mainModel.loginNotSuccessful();
        }
    }
}

void MainController::processRelations(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(FriendAction::FRIEND_REMOVE)) {
        m_mainModel.removeFriend(request.at("friend_rm_receiver"));
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_ACCEPT)) {
        m_mainModel.addFriend(request.at("friend_req_receiver"));
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_REQUEST)) {
        m_mainModel.addFriendRequestReceived(request.at("friend_req_sender"));
    } else if (request.at("action") == toJsonString(FriendAction::FRIEND_REFUSE)) {
        m_mainModel.refuseFriendRequest(request.at("friend_req_sender"));
    }
}

void MainController::processChatBox(const std::string &serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(ChatInteraction::FRIEND_MESSAGE)) {
        m_mainModel.addFriendMessage(request.at("sender"), request.at("message"));
    }
    if (request.at("action") == toJsonString(ChatInteraction::IN_GAME_MESSAGE)) {
//        m_mainModel.addGameMessage(request.at("sender"), request.at("receivers").get<std::vector<std::string>>(), request.at("message"));
    }
}

void MainController::processGameSetup(const std::string &serRequest)
{
}

MainModel *MainController::getMainModel()
{
    return &m_mainModel;
}
