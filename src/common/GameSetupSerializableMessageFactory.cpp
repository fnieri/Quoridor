#include "GameSetupSerializableMessageFactory.h"
#include "MessageEnums/Domain.h"

using json = nlohmann::json;

json GameSetupSerializableMessageFactory::serializeGameSetup(GameMode gameMode, GameInvite gameInvite, std::vector<std::string> &players)
{
    json playerArray = json::array();
    for (auto &player : players)
        playerArray.push_back(player);

    json setupJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"action", toJsonString(gameInvite)}, {"game_mode", toJsonString(gameMode)}, {"players", playerArray}};
    return setupJson;
}

json GameSetupSerializableMessageFactory::serializeGameSetup(GameMode gameMode, GameInvite gameInvite, std::vector<std::string> &players, int time, int increment)
{
    json playerArray = json::array();
    for (auto &player : players)
        playerArray.push_back(player);

    json setupJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"action", toJsonString(gameInvite)}, {"game_mode", toJsonString(gameMode)}, {"players", playerArray}, {"time", time},
        {"increment", increment}};
    return setupJson;
}
