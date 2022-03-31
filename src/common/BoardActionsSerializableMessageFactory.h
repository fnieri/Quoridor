/**
 * @file BoardActionsSerializableMessageFactory.h
 * @author Francesco Nieri
 * @brief MessageFactory for Player userActions
 * @date 2022-02-19
 */

#pragma once

#include "../client/PlayerAction.h"
#include "../client/WallAction.h"
#include "MessageEnums/Actions/PlayerActions.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json_fwd.hpp>

#include <tuple>

class BoardActionsSerializableMessageFactory
{
public:
    /**
     * @brief Serialize a pawn action on the board
     *
     * @param pawnAction the non-serialized action done by a player,
     * @param playerID the ID corresponding to the color of the player's pawn
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
    static nlohmann::json serializePawnAction(PlayerAction pawnAction, int playerID);
    /**
     * @brief Serialize a wall action the board
     *
     * @param wallAction the non-serialized wall action done by a player.
     * @param playerID the ID corresponding to the color of the player's pawn
     * @return nlohmann::json Return a json as such
     * {
     *  "action" : "place_wall",
     *  "move" : {
     *      "wall_cell" : {
     *          "x" : 0,
     *          "y" : 0},
     *      "wall_orientation" : vwall_ertical | wall_horizontal
     *  },
     *  "player_id" : 1
     * }
     */
    static nlohmann::json serializeWallAction(WallAction wallAction, int playerID);
};
