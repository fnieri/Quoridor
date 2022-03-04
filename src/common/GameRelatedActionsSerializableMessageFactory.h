/**
 * @file GameRelatedActionsSerializableMessageFactory.h
 * @author Francesco Nieri
 * @brief Factory methods for gameRelated serialized messages
 * @date 2022-03-04
 *
 */

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
    static nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, const std::string &username, int ELO);

    /**
     * @brief Serialize a user request when pausing, saving, forfeiting game
     *
     * @param queueAction
     * @param gameMode GameMode for which he's joining
     * @param username User that is joining
     * @return nlohmann::json requestJson
     */
    static nlohmann::json serializeInGameRelatedRequest(GameAction gameAction, const std::string &username);

    /**
     * @brief Serialize a game starting up based on a configuration
     * @param gameID id of new game
     * @param configuration json configuration of new game
     * @return  serialied json of request as such
     * {
     * {"action", "start_game},
     * {"domain", "in_game_related"},
     * {"configuration", **json config**},
     * {"game_id", 123}
     * }
     */
    static nlohmann::json serializeGameStarted(int gameID, nlohmann::json configuration);
    /**
     * @brief Serialize a game ending
     * @param gameID id of ending game
     * @return serialized json as such
     * {
     * {"action", "end_game"},
     * {"domain", "in_game_related"},
     * {"game_id", 123}
     * }
     */
    static nlohmann::json serializeGameEnded(int gameID);
};
