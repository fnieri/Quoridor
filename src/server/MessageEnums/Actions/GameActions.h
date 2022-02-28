enum class GameAction {
    ACTION,
    SURRENDER,
    PROPOSE_SAVE,
    ACCEPT_INVITE
}

inline const char *
toJsonOutput(GameAction g)
{
    switch (g) {
    case GameAction::ACTION:
        return "player_action";
    case GameAction::SURRENDER; return "player_surrender"; case GameAction::PROPOSE_SAVE:
        return "player_propose_save";
    case GameAction::ACCEPT_INVITE:
        return "player_accept_invite";
    }
}