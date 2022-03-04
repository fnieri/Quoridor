/**
 * @file FriendActionsSerializableMessageFactory.h
 * @author Francesco Nieri
 * @brief Factory methods for friendActions serialized messages
 * @date 2022-03-04
 *
 */

#pragma once

#include "MessageEnums/Actions/FriendActions.h"
#include <nlohmann/json.hpp>
#include <string>

class FriendActionsSerializableMessageFactory
{
public:
    /**
     * @brief Serialize a Friend Request
     * @param friendAction (friend_request | friend_accept | friend_refuse)
     * @param friendRequestSender request's sender
     * @param friendRequestReceiver request's receiver
     * @return json of Serialized request as such
     * {
     * {"action", "friend_request"},
     * {"domain", "relations"},
     * {"friend_req_sender", "me"},
     * {"friend_req_receiver", "you"}
     * }
     */
    static nlohmann::json serializeFriendRequest(FriendAction friendAction, const std::string &friendRequestSender, const std::string &friendRequestReceiver);
    /**
     * @brief Serialize a Friend removal
     * @param friendRemoveSender sender of removal
     * @param friendRequestRemover Removee
     * @return json of serialized request as such
     * {
     * {"action", "friend_remove"},
     * {"domain", "relations"},
     * {"friend_rm_sender", "you"},
     * {"friend_rm_receiver, "me}
     * }
     */
    static nlohmann::json serializeFriendRemove(const std::string &friendRemoveSender, const std::string &friendRequestRemover);
};
