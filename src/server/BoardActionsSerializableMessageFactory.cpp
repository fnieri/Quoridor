/**
 * @file BoardActionsSerializableMessageFactory.cpp
 * @author Francesco Nier
 * @date 2022-02-21
 *
 */

#include "BoardActionsSerializableMessageFactory.h"

#include "../client/PlayerAction.h"

using json = nlohmann::json;

json BoardActionsSerializableMessageFactory::serializePawnAction(PlayerAction pawnAction, int playerID)
{
    json actionJson = {{"action", toJsonString(JsonPlayerAction::MOVE_PAWN)}, {"move", pawnAction.serialized()}, {"player_id", playerID}};
    return actionJson;
}

json BoardActionsSerializableMessageFactory::serializeWallAction(WallAction wallAction, int playerID)
{
    json actionJson = {{"action", toJsonString(JsonPlayerAction::PLACE_WALL)}, {"move", wallAction.serialized()}, {"player_id", playerID}};
    return actionJson;
}
