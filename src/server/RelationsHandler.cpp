/**
 * @file RelationsHandler.cpp
 * @author Boris Petrov
 * @brief Everything to do with friends
 * @date 02/25/22
 */

#include "RelationsHandler.h"
#include "FriendActionsSerializableMessageFactory.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * RelationsHandler
 */

RelationsHandler::RelationsHandler(UserHub &userHub)
    : m_userHub {userHub}
{
}

void RelationsHandler::recordFriendAction(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    if (request["action"] == toJsonString(FriendActions::FRIEND_REQUEST)) {
        DatabaseHandler::sendFriendRequest(request["friend_req_sender"], request["friend_req_receiver"]);

    } else if (request["action"] == toJsonString(FriendActions::FRIEND_ACCEPT)) {
        DatabaseHandler::acceptFriendRequest(request["friend_req_sender"], request["friend_req_receiver"]);

    } else if (request["action"] == toJsonString(FriendActions::FRIEND_REFUSE)) {
        DatabaseHandler::removeFriendRequest(request["friend_req_sender"], request["friend_req_receiver"]);

    } else if (request["action"] == toJsonString(FriendActions::FRIEND_REMOVE)) {
        DatabaseHandler::removeFriend(request["friend_rm_sender"], request["friend_rm_receiver"]);
    }
}

void relayFriendAction(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    if (request["action"] == toJsonString(FriendActions::FRIEND_REQUEST)) {
        m_userHub.relayMessageTo(request["friend_req_receiver"], serRequest);

    } else if (request["action"] == toJsonString(FriendActions::FRIEND_ACCEPT)) {
        m_userHub.relayMessageTo(request["friend_req_sender"], serRequest);

    } else if (request["action"] == toJsonString(FriendActions::FRIEND_REFUSE)) {
        m_userHub.relayMessageTo(request["friend_req_sender"], serRequest);

    } else if (request["action"] == toJsonString(FriendActions::FRIEND_REFUSE)) {
        m_userHub.relayMessageTo(request["friend_rm_receiver"], serRequest);
    }
}

void processRequest(const std::string &serRequest)
{
    recordFriendAction(serRequest);
    relayFriendAction(serRequest);
}
