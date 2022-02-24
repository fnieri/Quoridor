#pragma once

enum class FriendAction {
    FRIEND_REQUEST,
    FRIEND_ACCEPT,
    FRIEND_REMOVE,
    FRIEND_REFUSE
}

inline const char *toJsonString(FriendAction f)
{
  switch (f) {
      case FriendAction::FRIEND_REQUEST:
          return "friend_request";
      case FriendAction::FRIEND_ACCEPT:
          return "friend_accept";
      case FriendAction::FRIEND_REMOVE:
          return "friend_remove";
      case FriendAction::FRIEND_REFUSE:
          return "friend_refuse";
  }
    
}
