#pragma once

#include "MessageEnums/Actions/FriendActions.h"
#include <nlohmann/json.hpp>
#include <string>

class FriendActionsSerializableMessageFactory
{
public:
    static nlohmann::json serializeFriendRequest(FriendAction friendAction, std::string& friendRequestSender, std::string& friendRequestReceiver);

    static nlohmann::json serializeFriendRemove(std::string& friendRemoveSender, std::string& friendRequestRemover);
};
