#include "FriendActionsSerializableMessageFactory.h"

using json = nlohmann::json;

json serializeFriendAction(FriendAction friendAction, std::string sender, std::string receiver) 
{
    json friendJson = {
      {"action", toJsonString(friendAction)},
      {"sender" : sender},
      {"receiver" : receiver}
    };
    return friendJson;
}
