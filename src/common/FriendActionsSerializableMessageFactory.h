#pragma once

#include "MessageEnums/Actions/FriendActions.h"
#include <nlohmann/json.hpp>
#include <string>

class FriendActionsSerializableMessageFactory
{
public:
    static nlohmann::json serializeFriendRequest(FriendAction friendAction, const std::string &friendRequestSender, const std::string &friendRequestReceiver);

    static nlohmann::json serializeFriendRemove(const std::string &friendRemoveSender, const std::string &friendRequestRemover);
};
