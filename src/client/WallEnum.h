#pragma once
#include <stdexcept>
enum class WallOrientation { Vertical, Horizontal };

inline const char *toJsonOutput(WallOrientation w)
{
    switch (w) {
    case WallOrientation::Vertical:
        return "wall_vertical";
    case WallOrientation::Horizontal:
        return "wall_horizontal";
    }
    return "";
}

WallOrientation jsonToOrientation(std::string jsonOrientation)
{
    switch (jsonOrientation) {
    case "wall_vertical":
        return WallOrientation::Vertical;
    case "wall_horizontal":
        return WallOrientation::Horizontal;
    default:
        throw std::invalid_argument("Not a valid orientation");
    }

} 