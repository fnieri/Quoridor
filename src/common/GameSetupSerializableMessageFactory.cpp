#include "GameSetupSerializableMessageFactory.h"

using json = nlohmann::json;

json GameSetupSerializableMessageFactory::serializeGameSetup(GameMode gameMode, std::vector<std::string> players)
{
    json setupJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"game_mode", toJsonString(gameMode)}, {"players", j_vec(players)}};
    return setupJson;
}

json GameSetupSerializableMessageFactory::serializeGameSetup(GameMode gameMode, std::vector<std::string> players, int time, int increment)
{
    json setupJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"game_mode", toJsonString(gameMode)}, {"players", j_vec(players)}, {"time", time},
        {"increment", increment}};
    return setupJson;
}
