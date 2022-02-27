#include "ChatBoxSerializableMessageFactory.h"

#include <string>

using json = nlohmann::json;

json serializeInGameMessage(std::string sender, std::vector<std::string> receivers, std::string message, int gameID) 
{
    
    json messageJson = {{"action", toJsonString(ChatInteraction::USER_SEND_MESSAGE)}, {"domain", toJsonString(Domain::CHAT)}, {"game_id", gameID}, {"sender", sender}, {"receivers", j_vec(receivers)}, {"message", message}};
  return messageJson;
}



json serializeFriendMessage(std::string sender, std::string receiver, std::string message)
{
  std::vector<std::string> receivers = {receiver};
  json messageJson = {{"action", toJsonString(ChatInteraction::USER_SEND_MESSAGE)}, {"domain", toJsonString(Domain::CHAT)}, {"game_id", gameID}, {"sender", sender}, {"receivers", j_vec(receivers)}, {"message", message}};
  return messageJson;
}
