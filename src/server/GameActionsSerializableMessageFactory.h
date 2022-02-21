#pragma once

#include "../common/User.h"
#include "MessageEnums/Actions/GameActions.h"
#include "MessageEnums/Modes/GameModes.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

#include <memory>

class GameActionsSerializableMessageFactory : public SerializableMessageFactory
{
    /**
     * @brief Serialize a user request when joining/leaving queue  
     * 
     * @param queueAction   Leave/join queue
     * @param gameMode GameMode for which he's joining
     * @param user User that is joining
     * @return nlohmann::json requestJson
     */
    nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::shared_ptr<User> user);
    /**
     * @brief Serialize a user request when   
     * 
     * @param queueAction 
     * @param gameMode GameMode for which he's joining
     * @param user User that is joining
     * @return nlohmann::json requestJson
     */
    nlohmann::json serializeInGameRequest(GameAction gameAction, std::shared_ptr<User> user);
};
