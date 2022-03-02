#pragma once

#include "MessageEnums/Modes/GameModes.h"
#include <nlohmann/json.hpp>
#include "MessageEnums/Actions/GameActions.h"

class GameSetupSerializableMessageFactory
{
public:
    static nlohmann::json serializeGameSetup(GameMode gameMode, GameInvite gameInvite, std::vector<std::string> &players);

    static nlohmann::json serializeGameSetup(GameMode gameMode, GameInvite gameInvite,  std::vector<std::string> &players, int time, int increment);
};
