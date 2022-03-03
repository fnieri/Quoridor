#pragma once

enum class GameAction { ACTION, SURRENDER, PROPOSE_SAVE, ACCEPT_INVITE };

inline const char *toJsonString(GameAction g)
{
    switch (g) {
    case GameAction::ACTION:
        return "player_action";
    case GameAction::SURRENDER:
        return "player_surrender";
    case GameAction::PROPOSE_SAVE:
        return "player_propose_save";
    case GameAction::ACCEPT_INVITE:
        return "player_accept_invite";
    }
    return "";
}

enum class QueueAction { JOIN_QUEUE, LEAVE_QUEUE };

inline const char *toJsonString(QueueAction q)
{
    switch (q) {
    case QueueAction::JOIN_QUEUE:
        return "join_queue";
    case QueueAction::LEAVE_QUEUE:
        return "leave_queue";
    }
    return "";
}

enum class GameInvite { GAME_INVITE, GAME_ACCEPT_INVITE, GAME_REFUSE_INVITE };

inline const char *toJsonString(GameInvite g)
{
    switch (g) {
    case GameInvite::GAME_INVITE:
        return "game_invite";
    case GameInvite::GAME_ACCEPT_INVITE:
        return "game_accept_invite";
    case GameInvite::GAME_REFUSE_INVITE:
        return "game_refuse_invite";
    }
    return "";
}
