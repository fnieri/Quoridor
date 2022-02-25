#include "FriendActionsSerializableMessageFactory.h"

using json = nlohmann::json;

json FriendActionsSerializableMessageFactory::serializeFriendRequest(FriendAction friendAction, std::string friendRequestSender, std::string friendRequestReceiver) 
{
    json requestJson = {
      {"action", toJsonString(friendAction)},
      {"friend_req_sender", sender},
      {"friend_req_receiver", receiver}
    };
    return requestJson;
}

json FriendActionsSerializableMessageFactory::serializeFriendRemove(std::string friendRemoveSender, std::string friendRemoveReceiver)
{
  json removeJson = {
    {"action", toJsonString(FriendAction::FRIEND_REMOVE)},
    {"friend_rm_sender", friendRemoveSender},
    {"friend_rm_receiver", friendRemoveReceiver}
  };
  return removeJson;
}
