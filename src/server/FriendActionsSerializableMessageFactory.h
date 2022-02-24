#pragma once

#include <nlohmann/json.hpp>
#include "MessageEnums/Actions/FriendAction.h"
#include <string>

class FriendActionsSerializableMessageFactory {
    
  nlohmann::json serializeFriendAction(FriendAction friendAction, std::string sender, std::string receiver);
}
