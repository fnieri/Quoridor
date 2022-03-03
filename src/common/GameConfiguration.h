#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class Point;
enum class GameMode;

using Positions = std::vector<Point>;
using WallCount = std::vector<unsigned>;

class GameConfiguration
{
public:
    GameConfiguration(GameMode gameMode, unsigned, const Positions &, const Positions &, const WallCount &);
    GameConfiguration(const std::string &); // from file

    GameMode mode() const;
    unsigned numberOfPlayers() const;

    const Positions &playerPositions() const;
    const Positions &wallPositions() const;
    const WallCount &availableWalls() const;

    nlohmann::json serialized();

private:
    GameMode m_mode;
    unsigned m_numberOfPlayers; // 2 - 4

    // Fields mostly used to resume a game
    // from a file.
    Positions m_playerPositions;
    Positions m_wallPositions;
    WallCount m_availableWalls;
};
