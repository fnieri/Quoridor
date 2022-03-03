#include "GameConfiguration.h"

using json = nlohmann::json;

GameConfiguration::GameConfiguration(const std::string &)
{
    // TODO IDK how
}

GameConfiguration::GameConfiguration(
    GameMode gameMode, unsigned int numberOfPlayers, const Positions &playerPositions, const Positions &wallPositions, const WallCount &numberOfWalls)
    : m_numberOfPlayers {numberOfPlayers}
    , m_playerPositions {playerPositions}
    , m_wallPositions {wallPositions}
    , m_availableWalls {numberOfWalls}
    , m_mode(gameMode)
{
}
