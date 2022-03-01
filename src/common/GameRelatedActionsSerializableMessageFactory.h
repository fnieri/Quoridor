#pragma once

#include "MessageEnums/Actions/GameActions.h"
#include "MessageEnums/Modes/GameModes.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

#include <memory>

class GameRelatedActionsSerializableMessageFactory
{
public:
    /**
     * @brief Serialize a user request when joining/leaving queue
     *
     * @param queueAction   Leave/join queue
     * @param gameMode GameMode for which he's joining
     * @param username User that is joining
     * @param ELO of user who's joining
     * @return nlohmann::json requestJson
     */
    static nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::string &username, int ELO);

    /**
     * @brief Serialize a user request when pausing, saving, forfeiting game
     *
     * @param queueAction
     * @param gameMode GameMode for which he's joining
     * @param username User that is joining
     * @return nlohmann::json requestJson
     */
    static nlohmann::json serializeInGameRelatedRequest(GameAction gameAction, std::string &username);
};
