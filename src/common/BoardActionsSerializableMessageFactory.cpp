/**
 * @file BoardActionsSerializableMessageFactory.cpp
 * @author Francesco Nier
 * @date 2022-02-21
 *
 */

#include "BoardActionsSerializableMessageFactory.h"

#include "../client/PlayerAction.h"

#include "MessageEnums/Domain.h"

using json = nlohmann::json;

json BoardActionsSerializableMessageFactory::serializePawnAction(PlayerAction pawnAction, int playerID)
{
    json actionJson = {{"action", toJsonString(JsonPlayerAction::MOVE_PAWN)}, {"domain", toJsonString(Domain::IN_GAME_RELATED)},
        {"move", pawnAction.serialized()}, {"player_id", playerID}};
    return actionJson;
}

json BoardActionsSerializableMessageFactory::serializeWallAction(WallAction wallAction, int playerID)
{
    json actionJson = {{"action", toJsonString(JsonPlayerAction::PLACE_WALL)}, {"domain", toJsonString(Domain::IN_GAME_RELATED)},
        {"move", wallAction.serialized()}, {"player_id", playerID}};
    return actionJson;
}
