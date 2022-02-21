/**
 * @file BoardActionsSerializableMessageFactory.h
 * @author Francesco Nieri
 * @brief MessageFactory for Player userActions
 * @date 2022-02-19
 * 
 * 
 */

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
    /**
     * @brief Serialize a pawn action on the board
     * 
     * @param playerAction JsonPlayerAction::MOVE_PAWN 
     * @param pawnAction the non-serialized action done by a player, 
     * @return nlohmann::json Return a json as such
     * {
     * "action" : "move_pawn",
     * "move" : {
     *      "initial_position" : {
     *          "x" : 0,
     *          "y" :  1}
     *      },
     *      "end_position" : {
     *          "x" : 1,
     *          "y" : 1},
     * "player_id" : 0
     * }
     */
    nlohmann::json serializePawnAction(JsonPlayerAction playerAction, PlayerAction pawnAction);
    /**
     * @brief Serialize a wall action the board
     * 
     * @param playerAction JsonPlayerAction::PLACE_WALL
     * @param wallAction the non-serialized wall action done by a player.
     * @return nlohmann::json Return a json as such
     * {
     *  "action" : "place_wall",
     *  "move" : {
     *      "wall_cell" : {
     *          "x" : 0,
     *          "y" : 0},
     *      "wall_orientation" : vertical | horizontal
     *  },
     *  "player_id" : 1
     * }
     */
    nlohmann::json serializeWallAction(JsonPlayerAction playerAction, WallAction wallAction);
};
