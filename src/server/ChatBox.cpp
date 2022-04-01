/**
 * @file ChatBox.cpp
 * @author Boris Petrov
 * @brief Handler of chat requests
 * @date 02/25/22
 */

#include "ChatBox.h"

#include "Database.h"
#include "UserHandler.h"
#include "src/common/SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

ChatBox::ChatBox(UserHub &userHub)
    : m_userHub {userHub}
{
}

auto ChatBox::processRequest(const std::string &serMessage) -> void
{
    recordMessage(serMessage);
    std::cout << "ChatBox::processRequest" << std::endl;
    relayMessage(serMessage);
}

auto ChatBox::recordMessage(const std::string &serRequest) -> void
{
    std::cout <<  serRequest << std::endl;
    auto request = json::parse(serRequest);

    std::string sender = request["sender"];
    std::string message = request["message"];

    std::cout << "ChatBox::recordMessage" << std::endl;
    if (request["action"] == toJsonString(ChatInteraction::FRIEND_MESSAGE)) {
        std::string receiver = request["receiver"];
        DatabaseHandler::recordMessage(sender, receiver, message);

    } else if (request["action"] == toJsonString(ChatInteraction::IN_GAME_MESSAGE)) {
        int game_id = request["game_id"];
        DatabaseHandler::recordMessage(sender, message, game_id);
    }
}

auto ChatBox::relayMessage(const std::string &serRequest) -> void
{
    auto request=  json::parse(serRequest);

    // Works only for one to one conversations
    std::string receiver = request["receiver"];
    m_userHub.relayMessageTo(receiver, serRequest);
}
