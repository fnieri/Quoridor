/**
 * @file ChatBoxSerializableMessageFactory.h
 * @author Francesco
 * @brief Factory methods for chatbox serialized messages
 * @date 2022-02-17
 *
 */

#pragma once

#include "MessageEnums/Actions/ChatBoxActions.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

class ChatBoxSerializableMessageFactory
{
public:
    /**
     * @brief Serialize message being sent in a match
     *
     * @param username Username of sender
     * @param message Message of sender
     * @return nlohmann::json as such
     * {
     *  "action" : "send_message",
     *  "sender" : "sox",
     *  "message" : "message",
     *  "game_id" : 123,
     * }
     */
    static nlohmann::json serializeInGameMessage(std::string& sender, std::vector<std::string>& receivers, std::string& message, int gameID);
    /**
     * @brief Serialize message being sent in a match
     *
     * @param username Username of sender
     * @param message Message of sender
     * @return nlohmann::json as such
     * {
     *  "action" : "send_message",
     *  "sender" : "sox",
     *  "receiver" : "igha",
     *  "message" : "message",
     * }
     */
    static nlohmann::json serializeFriendMessage(std::string& sender, std::string& receiver, std::string& message);
};
