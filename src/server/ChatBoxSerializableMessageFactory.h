/**
 * @file ChatBoxSerializableMessageFactory.cpp
 * @author Francesco
 * @brief Factory methods for chatbox serialized messages
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "MessageEnums/Actions/ChatBoxActions.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

class ChatBoxSerializableMessageFactory : public SerializableMessageFactory
{
public:
    nlohmann::json serializeUserChatBoxRequest(ChatInteraction interaction, int chatboxId, std::string username, std::string message, int timestamp);
};