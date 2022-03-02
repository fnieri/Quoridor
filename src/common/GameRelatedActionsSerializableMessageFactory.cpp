#include "GameRelatedActionsSerializableMessageFactory.h"

#include "MessageEnums/Domain.h"

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
