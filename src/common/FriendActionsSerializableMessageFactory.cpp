/**
* @file FriendActionsSerializableMessageFactory.h
* @author Francesco
* @brief Factory methods for friendActions serialized messages
* @date 2022-03-04
*
 */


#include "FriendActionsSerializableMessageFactory.h"

#include "MessageEnums/Domain.h"

using json = nlohmann::json;

json FriendActionsSerializableMessageFactory::serializeFriendRequest(
    FriendAction friendAction, const std::string &friendRequestSender, const std::string &friendRequestReceiver)
{
    json requestJson = {{"action", toJsonString(friendAction)}, {"domain", toJsonString(Domain::RELATIONS)}, {"friend_req_sender", friendRequestSender},
        {"friend_req_receiver", friendRequestReceiver}};
    return requestJson;
}

json FriendActionsSerializableMessageFactory::serializeFriendRemove(const std::string &friendRemoveSender, const std::string &friendRemoveReceiver)
{
    json removeJson = {{"action", toJsonString(FriendAction::FRIEND_REMOVE)}, {"domain", toJsonString(Domain::RELATIONS)},
        {"friend_rm_sender", friendRemoveSender}, {"friend_rm_receiver", friendRemoveReceiver}};
    return removeJson;
}
