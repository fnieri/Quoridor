/**
 * @file ChatBoxSerializableMessageFactory.cpp
 * @author Francesco
 * @brief Factory methods for chatbox serialized messages
 * @version 0.1
 * @date 2022-02-17
 *
 *
 */

#pragma once

#include "MessageEnums/Actions/ChatBoxActions.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

class ChatBoxSerializableMessageFactory : public SerializableMessageFactory
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
     * @return nlohmann::json 
     */
    nlohmann::json serializeUserChatBoxRequest(ChatInteraction interaction, int chatboxId, std::string username, std::string message, int timestamp);
};