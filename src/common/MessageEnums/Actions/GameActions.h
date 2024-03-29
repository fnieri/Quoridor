#pragma once

enum class GameAction { ACTION, SURRENDER, PROPOSE_SAVE, ACCEPT_SAVE, REFUSE_SAVE, ACCEPT_INVITE, START_GAME, END_GAME };

inline const char *toJsonString(GameAction g)
{
    switch (g) {
    case GameAction::ACTION:
        return "player_action";
    case GameAction::SURRENDER:
        return "player_surrender";
    case GameAction::PROPOSE_SAVE:
        return "player_propose_save";
    case GameAction::ACCEPT_SAVE:
        return "player_accept_save";
    case GameAction::REFUSE_SAVE:
        return "player_refuse_save";
    case GameAction::ACCEPT_INVITE:
        return "player_accept_invite";
    case GameAction::START_GAME:
        return "game_start";
    case GameAction::END_GAME:
        return "game_end";
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

enum class GameSetup { JOIN_GAME, QUIT_GAME, CREATE_GAME };

inline const char *toJsonString(GameSetup g)
{
    switch (g) {
    case GameSetup::JOIN_GAME:
        return "join_game";
    case GameSetup::QUIT_GAME:
        return "quit_game";
    case GameSetup::CREATE_GAME:
        return "create_game";
    }
    return "";
}
