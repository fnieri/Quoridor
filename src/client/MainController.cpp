#include "MainController.h"

void MainController::processRequest(const std::string& serRequest)
{
    json request(json::parse(serRequest));
    if (request["domain"] == toJsonString(Domain::AUTH)) {
        processAuth(serRequest);
    } else if (request["domain"] == toJsonString(Domain::RELATIONS)) {
        processRelations(serRequest);
    } else if (request["domain"] == toJsonString(Domain::CHAT)) {
        processChatbox(serRequest);
    } else if (request["domain"] == toJsonString(Domain::RESOURCE_REQUEST)) {
        processResourceRequest(serRequest);
    } else if (request["domain"] == toJsonString(Domain::IN_GAME_RELATED)) {
        processGameAction(serRequest);
    } else if (request["domain"] == toJsonString(Domain::GAME_SETUP)) {
        processGameSetup(serRequest);
    }
}

void MainController::processResourceRequest(const std::string &)
{
    json request(json::parse(serRequest));

    if (request.at("action") == toJsonString(DataType::LEADERBOARD)) {
        std::vector<std::pair<std::string, float> leaderboard;
        for (auto it = request.at("serialized_data").begin(); it != request.at("serialized_data").end(); it++)
            leaderboard.push_back(std::pair<std::string, float>(request.at("username"), request.at("elo")));
        mainModel.sendLeadeboard(leaderboard);
    }else if (request.at("action") == toJsonString(DataType::FRIENDS_LIST)) {

    }else if (request.at("action") == toJsonString(DataType::GAME_CONFIG)) {

    }else if (request.at("action") == toJsonString(DataType::FRIEND_REQUESTS_SENT)) {

    }else if (request.at("action") == toJsonString(DataType::FRIEND_REQUESTS_RECEIVED)) {

    }else if (request.at("action") == toJsonString(DataType::GAME_IDS)) {

    }else if (request.at("action") == toJsonString(DataType::CHATS)) {

    }else if (request.at("action") == toJsonString(DataType::ELO)) {

    }
}


void MainController::processAuth(const std::string& serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(ClientAuthAction::LOGIN)) {
        if (request.at("status") == toJsonString(Status::SUCCESS)) {
            mainModel.loginSuccessful(request.at("username"));
        }
        else if (request.at("status") == toJsonString(Status::FAILURE)) {
            mainModel.loginNotSuccessful(request.at("username"))
        }
    }
}

void MainController::processRelations(const std::string& serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(FriendAction::FRIEND_REMOVE)) {
        mainModel.removeFriend(request.at("friend_rm_receiver"));
    }
    else if (request.at("action") == toJsonString(FriendAction::FRIEND_ACCEPT)) {
        mainModel.addFriend(request.at("friend_req_receiver"));
    }
    else if (request.at("action") == toJsonString(FriendAction::FRIEND_REQUEST)) {
        mainModel.addFriendRequest(request.at("friend_req_sender"));
    }
    else if (request.at("action") == toJsonString(FriendAction::FRIEND_REFUSE)) {
        mainModel.removeFriendRequest(request.at("friend_req_sender"));
    }
}

void MainController::processChatbox(const std::string& serRequest)
{
    json request(json::parse(serRequest));
    if (request.at("action") == toJsonString(ChatInteraction::FRIEND_MESSAGE)) {
        mainModel.addFriendMessage(request.at("sender"), request.at("receiver"), request.at("message"));
    }
    if (request.at("action") == toJsonString(ChatInteraction::IN_GAME_MESSAGE)) {
        MainModel.addGameMessage(request.at("sender"), request.at("receivers").get<std::vector<std::string>>());
    }
}

void MainController::processGameSetup(const std::string& serRequest)
{

}
