// Written by Francesco Nieri

#include "BoardActionsSerializableMessageFactory.h"

#include "../client/PlayerAction.h"
#include <assert.h>

using json = nlohmann::json;

json BoardActionsSerializableMessageFactory::serializePawnAction(JsonPlayerAction playerAction, PlayerAction pawnAction) 
{   
    assert(playerAction == JsonPlayerAction::MOVE_PAWN);
    json actionJson = {
        {"action", toJsonOutput(playerAction)},
        {"move", pawnAction.serialized()}
    };
    return actionJson;
}

json BoardActionsSerializableMessageFactory::serializeWallAction(JsonPlayerAction playerAction, WallAction wallAction) {
    assert(playerAction == JsonPlayerAction::PLACE_WALL);
    json actionJson = {
        {"action", toJsonOutput(playerAction)},
        {"move", wallAction.serialized()}
    };
    return actionJson;
}

