#include "ChatBoxSerializableMessageFactory.h"
#include <iostream>

Json::Value ChatBoxSerializableMessageFactory::serializeUserChatBoxRequest(
    ChatInteraction interaction, int chatboxId, std::string username, std::string message, int timestamp)
{
    Json::Value returnJson;
    returnJson["action"] = toJsonString(interaction);
    returnJson["chatbox_id"] = chatboxId;
    returnJson["username"] = username;
    returnJson["message"] = (interaction == ChatInteraction::USER_SEND_MESSAGE) ? message : "";
    returnJson["timestamp"] = timestamp;
    return returnJson;
}
