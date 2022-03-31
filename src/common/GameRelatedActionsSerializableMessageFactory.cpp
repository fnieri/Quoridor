#include "GameRelatedActionsSerializableMessageFactory.h"

#include "MessageEnums/Domain.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

json GameRelatedActionsSerializableMessageFactory::serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, const std::string &username, int ELO)
{
    json requestJson = {{"action", toJsonString(queueAction)}, {"domain", toJsonString(Domain::IN_GAME_RELATED)}, {"game_mode", toJsonString(gameMode)},
        {"username", username}, {"ELO", ELO}};
    return requestJson;
}

json GameRelatedActionsSerializableMessageFactory::serializeInGameRelatedRequest(GameAction gameAction, const std::string &username)
{
    json requestJson = {
        {"action", toJsonString(gameAction)},
        {"domain", toJsonString(Domain::IN_GAME_RELATED)},
        {"username", username},
    };
    return requestJson;
}

json GameRelatedActionsSerializableMessageFactory::serializeGameStarted(int gameID, nlohmann::json configuration)
{
    json gameJson = {{"action", toJsonString(GameAction::START_GAME)}, {"domain", toJsonString(Domain::IN_GAME_RELATED)}, {"configuration", configuration},
        {"game_id", gameID}};
    return gameJson;
}

json GameRelatedActionsSerializableMessageFactory::serializeGameEnded(int gameID)
{
    json endJson = {{"action", toJsonString(GameAction::END_GAME)}, {"domain", toJsonString(Domain::IN_GAME_RELATED)}, {"game_id", gameID}};
    return endJson;
}
