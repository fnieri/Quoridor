#pragma once
#include <stdexcept>

/// The two possible orientations for a wall and a Corridor within a Board.
enum class WallOrientation { Vertical, Horizontal };

/**
 * Convert a given WallOrientation to string to use for json serializing.
 *
 * @param w the WallOrientation to convert
 * @returns const char*
 */
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

/**
 * Convert a given string to WallOrientation enum type.
 *
 * @param jsonOrientation the string to convert to WallOrientation
 * @returns WallOrientation
 */
/*
WallOrientation jsonToOrientation(std::string jsonOrientation)
{
    // Use if-else because switch can't be used on strings
    if (jsonOrientation == "wall_vertical")
        return WallOrientation::Vertical;
    else if (jsonOrientation == "wall_horizontal")
        return WallOrientation::Horizontal;
    else
        throw std::invalid_argument("Not a valid orientation");
} */