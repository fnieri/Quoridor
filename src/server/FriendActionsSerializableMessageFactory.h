#pragma once

#include <nlohmann/json.hpp>
#include "MessageEnums/Actions/FriendActions.h"
#include <string>

class FriendActionsSerializableMessageFactory {
  public:
  static nlohmann::json serializeFriendRequest(FriendAction friendAction, std::string friendRequestSender, std::string friendRequestReceiver);

  static nlohmann::json serializeFriendRemove(std::string friendRemoveSender, std::string friendRequestRemover);
};
