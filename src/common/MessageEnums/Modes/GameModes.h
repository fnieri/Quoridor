#pragma once

enum class GameMode { CLASSIC, TIMER, QUOTETRIS, FOG_OF_WAR };

inline const char *toJsonString(GameMode g)
{
    switch (g) {
    case GameMode::CLASSIC:
        return "classic_mode";
    case GameMode::TIMER:
        return "timer_mode";
    case GameMode::QUOTETRIS:
        return "tetris_mode";
    case GameMode::FOG_OF_WAR:
        return "fow_mode"; // FOW == Fog Of War
    }
    return "";
}
