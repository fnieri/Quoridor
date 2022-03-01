#include "FriendActionsSerializableMessageFactory.h"

#include "MessageEnums/Domain.h"

using json = nlohmann::json;

json FriendActionsSerializableMessageFactory::serializeFriendRequest(
    FriendAction friendAction, std::string friendRequestSender, std::string friendRequestReceiver)
{
    json requestJson = {{"action", toJsonString(friendAction)}, {"domain", toJsonString(Domain::RELATIONS)}, {"friend_req_sender", friendRequestSender},
        {"friend_req_receiver", friendRequestReceiver}};
    return requestJson;
}

json FriendActionsSerializableMessageFactory::serializeFriendRemove(std::string friendRemoveSender, std::string friendRemoveReceiver)
{
    json removeJson = {{"action", toJsonString(FriendAction::FRIEND_REMOVE)}, {"domain", toJsonString(Domain::RELATIONS)},
        {"friend_rm_sender", friendRemoveSender}, {"friend_rm_receiver", friendRemoveReceiver}};
    return removeJson;
}
