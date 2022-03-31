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

#include <nlohmann/json_fwd.hpp>

class ChatBoxSerializableMessageFactory
{
public:
    /**
     * @brief Serialize message being sent in a match
     *
     * @param sender username of sender
     * @param receivers
     * @return nlohmann::json as such
     * {
     *  "action" : "in_game_message",
     *  "sender" : "sox",
     *  "receivers" : ["nobody", "but", "me"],
     *  "message" : "message",
     *  "game_id" : 123,
     * }
     */
    static nlohmann::json serializeInGameMessage(const std::string &sender, std::vector<std::string> &receivers, const std::string &message, int gameID);
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
    static nlohmann::json serializeFriendMessage(const std::string &sender, const std::string &receiver, const std::string &message);
};
