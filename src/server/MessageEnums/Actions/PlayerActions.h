#pragma once

enum class JsonPlayerAction {
    PLACE_WALL,
    MOVE_PAWN
};

inline const char *toJsonOutput(JsonPlayerAction p) {
    switch (p)
    {
        case JsonPlayerAction::PLACE_WALL:
            return "place_wall";
        case JsonPlayerAction::MOVE_PAWN:
            return "move_pawn";
    }
    return "";
}
