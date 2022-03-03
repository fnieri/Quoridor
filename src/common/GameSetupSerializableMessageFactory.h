#pragma once

#include "MessageEnums/Actions/GameActions.h"
#include "MessageEnums/Modes/GameModes.h"
#include <nlohmann/json.hpp>

class GameSetupSerializableMessageFactory
{
public:
    static nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string> &players);

    static nlohmann::json serializeGameParticipationRequest(GameSetup gameSetup, int gameID);

    static nlohmann::json serializeGameCreationRequest(const std::string& sender, std::vector<std::string>& receivers, nlohmann::json configuration);

    // static nlohmann::json serializeGameStarted(int gameID, GameConfiguration gameConfiguration);
};
