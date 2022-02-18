#pragma once

enum class WallOrientation { Vertical, Horizontal };

inline const char *toJsonOutput(WallOrientation w)
{
    switch (w) {
        case WallOrientation::Vertical:
            return "wall_vertical";
        case WallOrientation::Horizontal:
            return "wall_horizontal";
    }
}