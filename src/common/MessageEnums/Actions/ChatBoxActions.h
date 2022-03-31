#pragma once

enum class ChatInteraction { FRIEND_MESSAGE, IN_GAME_MESSAGE };

inline const char *toJsonString(ChatInteraction a)
{
    switch (a) {
    case ChatInteraction::FRIEND_MESSAGE:
        return "friend_message";
    case ChatInteraction::IN_GAME_MESSAGE:
        return "in_game_message";
    }
    return "";
}
