#include "GameSetupSerializableMessageFactory.h"
#include "MessageEnums/Domain.h"

using json = nlohmann::json;

json GameSetupSerializableMessageFactory::serializeGameSetup(GameMode gameMode, std::vector<std::string> &players)
{
    json playerArray = json::array();
    for (auto &player : players)
        playerArray.push_back(player);

    json setupJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"action", toJsonString(GameSetup::CREATE_GAME)}, {"game_mode", toJsonString(gameMode)},
        {"players", playerArray}};
    return setupJson;
}

json GameSetupSerializableMessageFactory::serializeGameParticipationRequest(GameSetup gameSetup, int gameID)
{

    json participationJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"action", toJsonString(gameSetup)}, {"game_id", gameID}};
    return participationJson;
}

json GameSetupSerializableMessageFactory::serializeGameCreationRequest(
    const std::string &sender, std::vector<std::string> &receivers, nlohmann::json configuration)
{
    json receiversArray = json::array();
    for (auto &player : receivers)
        receiversArray.push_back(player);

    json creationJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"action", toJsonString(GameSetup::CREATE_GAME)}, {"sender", sender},
        {"receivers", receiversArray}, {"configuration", configuration}};
    return receiversArray;
}
/*
json GameSetupSerializableMessageFactory::serializeGameSetup(
    GameMode gameMode, std::vector<std::string> &players, int time, int increment)

{
    json playerArray = json::array();
    for (auto &player : players)
        playerArray.push_back(player);

    json setupJson = {{"domain", toJsonString(Domain::GAME_SETUP)}, {"action", toJsonString(gameInvite)}, {"game_mode", toJsonString(gameMode)},
        {"players", playerArray}, {"time", time}, {"increment", increment}};
    return setupJson;
}
*/
