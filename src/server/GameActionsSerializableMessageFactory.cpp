#include "GameActionsSerializableMessageFactory.h"

using json = nlohmann::json;

json GameActionsSerializableMessageFactory::serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::shared_ptr<User> user)
{
    json requestJson
        = {{"action", toJsonString(queueAction)}, {"game_mode", toJsonString(gameMode)}, {"username", user->getUsername()}, {"ELO", user->getELO()}};
    return requestJson;
}

json GameActionsSerializableMessageFactory::serializeInGameRequest(GameAction gameAction, std::shared_ptr<User> user)
{
    json requestJson = {
        {"action", toJsonString(gameAction)},
        {"username", user->getUsername()},
    };
    return requestJson;
}
