#include "GameActionsSerializableMessageFactory.h"

using json = nlohmann::json;

json GameActionsSerializableMessageFactory::serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::string username, int ELO)
{
    json requestJson
        = {{"action", toJsonString(queueAction)}, 
          {"domain", toJsonString(Domain::IN_GAME_RELATED)}, {"game_mode", toJsonString(gameMode)}, {"username", username}, {"ELO", ELO}};
    return requestJson;
}

json GameActionsSerializableMessageFactory::serializeInGameRequest(GameAction gameAction, std::string username)
{
    json requestJson = {
        {"action", toJsonString(gameAction)},
        {"domain", toJsonString(Domain::IN_GAME_RELATED)},
        {"username", username},
    };
    return requestJson;
}
