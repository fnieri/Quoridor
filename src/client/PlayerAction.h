#pragma once

#include "src/common/Serializable.h"
#include "Board.h"
#include "Player.h"
#include "PlayerEnum.h"
#include "src/common/Point.h"

#include <nlohmann/json.hpp>

#include <memory>
#include <string>

/**
 * Represents a potential pawn-move action to be performed by a Player.
 *
 * @see WallAction for the analogous action for wall placement.
 */
class PlayerAction
{
    /// A reference to the Board to perform the action on.
    std::shared_ptr<Board> board;

    /// A reference to the Player performing the action.
    std::shared_ptr<Player> player;

    /**
     * The position at which to move the Player performing the action.
     *
     * @warning is a *proper matrix position*
     */
    Point destination;

public:
    /**
     * Construct a new PlayerAction
     *
     * @param board the Board to perform the action on
     * @param player the Player performing the action
     * @param _destination the cell to which the Player will move through the action.
     *
     * @warning the given destination is assumed to be *player cell position*
     */
    PlayerAction(std::shared_ptr<Board> board, std::shared_ptr<Player> player, const Point &_destination);

    /**
     * Check if the player move is valid according to the game rules.
     *
     * @returns bool
     */
    bool isActionValid();

    /**
     * Check if the game has a winner.
     *
     * @returns bool
     */
    bool isGameOver();

    /**
     * Play the move, if it is valid.
     *
     * @returns bool whether or not the move was executed
     */
    bool executeAction();

    /**
     * Serialize the PlayerAction to json format.
     *
     * @returns \ref nlohmann::json
     */
    nlohmann::json serialized();
};
