#pragma once

#include "Board.h"
#include "Player.h"
#include "WallEnum.h"

#include <nlohmann/json.hpp>

#include <memory>

/**
 * Represents a potential wall-place action to be performed by a Player.
 *
 * @see PlayerAction for the analogous action for pawn movement.
 */
class WallAction
{
private:
    /// A reference to the Board to perform the action on.
    std::shared_ptr<Board> board;

    /// A reference to the Player performing the action.
    std::shared_ptr<Player> player;

    /**
     * "Destination" of the wall
     *
     * @warning is a *player cell position*
     *
     * @note the destination cell represents the player cell above or left of the wall, depending on the orientation of said wall.
     */
    Point destCell;

    /**
     * @brief
     *
     * @note the orientation of the wall dictates its placement relative to the destination cell:
     * - if orienation is WallOrientation::Vertical, the wall is placed to the right of cell and continues towards the bottom
     * - if orienation is WallOrientation::Horizontal, the wall is placed under cell and continues towards the right
     */
    WallOrientation orientation;

    /**
     * Returns the position of the first piece of the wall to be placed on the Board.
     *
     * @returns Point
     *
     * @warning the returned position is a *proper matrix position*
     * @see WallAction#piece2 for the second piece.
     */
    Point piece1();

    /**
     * Returns the position of the second piece of the wall to be placed on the Board.
     *
     * @returns Point
     *
     * @warning the returned position is a *proper matrix position*
     * @see WallAction#piece1 for the first piece.
     */
    Point piece2();

public:
    /**
     * Construct a new WallAction.
     *
     * @param board the Board to perform the action on
     * @param player the Player performing the action
     * @param destCell the destination player cell to place the wall next to
     * @param orientation the orientation of the wall to be placed
     */
    WallAction(std::shared_ptr<Board> board, std::shared_ptr<Player> player, const Point &destCell, const WallOrientation &orientation);

    ~WallAction();

    /**
     * Checks if the wall placement of this action is *legal*, meaning it doesn't obstruct any Player from reaching their finish line.
     *
     * @returns bool
     */
    bool isWallPlacementLegal();

    /**
     * Checks if the wall placement of this action is *valid*, meaning it doesn't intersect with other walls or go out of bounds.
     *
     * @returns bool
     */
    bool isWallPlacementValid();

    /**
     * Place the wall on the Board, if the placement is valid and legal.
     *
     * @returns bool whether or not the action was executed
     */
    bool executeAction();

    /**
     * @brief Return serialized json of a WallAction as such
     *
     * {
     *  wall_cell : {
     *    x : 0,
     *    y : 0
     *    }
     *  wall_orientation
     * }
     *
     * @returns \ref nlohmann::json
     */
    nlohmann::json serialized();
};
