/**
 * @file ChatBoxSerializableMessageFactory.h
 * @author Francesco
 * @brief Factory methods for chatbox serialized messages
 * @version 0.1
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
     * @brief
     *
     * @param interaction User interaction with chatbox
     * @param chatboxId Id of chatbox in database (Is it necessary for temp ones? Idk)
     * @param username Username of sender
     * @param message Message of sender
     * @param timestamp Time since epoch of message
     * @return nlohmann::json as such
     * {
     *  "action" : "send_message | join_chatbox | leave_chatbox",
     *  "chatbox_id" : "124" //The ID of the chatbox in the database
     *  "username" : "sox",
     *  "message" : blank if user is joining|leaving chat or message sent if "send_message",
     *  "timestamp" : "1236762548123482"  // time since epoch of message
     * }
     */
    static nlohmann::json serializeUserChatBoxRequest(ChatInteraction interaction, int chatboxId, std::string username, std::string message, int timestamp);
};
