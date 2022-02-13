#pragma once

#include "MessageEnums/Actions/ChatBoxActions.h"
#include "SerializableMessageFactory.h"

class ChatBoxSerializableMessageFactory : public SerializableMessageFactory
{
public:
    Json::Value serializeUserChatBoxRequest(ChatInteraction interaction, int chatboxId, std::string username, std::string message, int timestamp);
};