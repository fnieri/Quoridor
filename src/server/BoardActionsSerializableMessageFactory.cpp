/**
 * @file BoardActionsSerializableMessageFactory.cpp
 * @author Francesco Nier
 * @date 2022-02-21
 * 
 */

#include "BoardActionsSerializableMessageFactory.h"

#include "../client/PlayerAction.h"
#include <assert.h>

using json = nlohmann::json;

json BoardActionsSerializableMessageFactory::serializePawnAction(JsonPlayerAction playerAction, PlayerAction pawnAction, int playerID)
{
    assert(playerAction == JsonPlayerAction::MOVE_PAWN);
    json actionJson = {{"action", toJsonOutput(playerAction)}, {"move", pawnAction.serialized()}, {"player_id", playerID}};
    return actionJson;
}

json BoardActionsSerializableMessageFactory::serializeWallAction(JsonPlayerAction playerAction, WallAction wallAction, int playerID)
{
    assert(playerAction == JsonPlayerAction::PLACE_WALL);
    json actionJson = {{"action", toJsonOutput(playerAction)}, {"move", wallAction.serialized()}, {"player_id", playerID}};
    return actionJson;
}
