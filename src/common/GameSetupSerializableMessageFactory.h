#pragma once

#include "MessageEnums/Modes/GameModes.h"
#include <nlohmann/json.hpp>

class GameSetupSerializableMessageFactory
{
public:

    static nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string>& players);

    static nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string>& players, int time, int increment);
};
