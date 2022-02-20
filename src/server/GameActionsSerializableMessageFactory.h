#pragma once

#include "SerializableMessageFactory.h"
#include "MessageEnums/Modes/GameModes.h"
#include "MessageEnums/Actions/GameActions.h"
#include "../common/User.h"

#include <nlohmann/json.hpp>

#include <memory>

class GameActionsSerializableMessageFactory : public SerializableMessageFactory 
{
  nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::shared_ptr<User> user);
  nlohmann::json serializeInGameRequest(GameAction gameAction, std::shared_ptr<User> user);
};


