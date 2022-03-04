#pragma once

enum class JsonPlayerAction { PLACE_WALL, MOVE_PAWN };

inline const std::string toJsonString(JsonPlayerAction p)
{
    switch (p) {
    case JsonPlayerAction::PLACE_WALL:
        return "place_wall";
    case JsonPlayerAction::MOVE_PAWN:
        return "move_pawn";
    }
    return "";
}
