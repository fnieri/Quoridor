#include "ChatBoxSerializableMessageFactory.h"

#include <string>

using json = nlohmann::json;

json ChatBoxSerializableMessageFactory::serializeUserChatBoxRequest(
    ChatInteraction interaction, int chatboxId, std::string username, std::string message, int timestamp)
{
    std::string actualMessage = (interaction == ChatInteraction::USER_SEND_MESSAGE) ? message : "";
    json ChatBoxRequestJson
        = {{"action", toJsonString(interaction)}, {"chatbox_id", chatboxId}, {"username", username}, {"message", actualMessage}, {"timestamp", timestamp}};

    return ChatBoxRequestJson;
}