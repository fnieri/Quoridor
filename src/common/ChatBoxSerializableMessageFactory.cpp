/**
 * @file ChatBoxSerializableMessageFactory.h
 * @author Francesco
 * @brief Factory methods for chatbox serialized messages
 * @date 2022-02-17
 *
 */

#include "ChatBoxSerializableMessageFactory.h"
#include "MessageEnums/Domain.h"

#include <string>

using json = nlohmann::json;

json ChatBoxSerializableMessageFactory::serializeInGameMessage(
    const std::string &sender, std::vector<std::string> &receivers, const std::string &message, int gameID)
{
    json receiversArray = json::array();
    for (auto &receiver : receivers)
        receiversArray.push_back(receiver);

    json messageJson = {{"action", toJsonString(ChatInteraction::IN_GAME_MESSAGE)}, {"domain", toJsonString(Domain::CHAT)}, {"game_id", gameID},
        {"sender", sender}, {"receivers", receiversArray}, {"message", message}};
    return messageJson;
}

json ChatBoxSerializableMessageFactory::serializeFriendMessage(const std::string &sender, const std::string &receiver, const std::string &message)
{
    json messageJson = {{"action", toJsonString(ChatInteraction::FRIEND_MESSAGE)}, {"domain", toJsonString(Domain::CHAT)}, {"sender", sender},
        {"receiver", receiver}, {"message", message}};
    return messageJson;
}
