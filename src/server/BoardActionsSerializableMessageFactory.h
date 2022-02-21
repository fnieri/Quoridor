#pragma once

#include "../client/PlayerAction.h"
#include "../client/WallAction.h"
#include "MessageEnums/Actions/PlayerActions.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

#include <tuple>

class BoardActionsSerializableMessageFactory : public SerializableMessageFactory
{
public:
    nlohmann::json serializePawnAction(JsonPlayerAction playerAction, PlayerAction pawnAction);
    nlohmann::json serializeWallAction(JsonPlayerAction playerAction, WallAction wallAction);
};
