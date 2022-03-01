#pragma once

#include <nlohmann/json.hpp>

class GameSetupSerializableMessageFactory
{
    nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string> players);

    nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string> players, int time, int increment);
}:
