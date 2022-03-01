#pragma once

#include "BoardComponent.h"
#include "Player.h"
#include "WallEnum.h"
#include "src/common/Point.h"

#include <memory>
#include <vector>

/**
 * Stores the data of the game board, notably wall and player positions.
 */
class Board
{
private:
    /**
     * The main matrix containing the walls and players as BoardComponent, specifically Corridor or Cell.
     * Direct access should be avoided to prevent index errors.
     */
    std::vector<std::vector<std::shared_ptr<BoardComponent>>> matrix;

    /// Number of player cells on the board (width and height).
    const int CELL_SIZE = 9;

    /// Size of the matrix, computed from CELL_SIZE.
    const int MATRIX_SIZE = (CELL_SIZE * 2) - 1;

    bool isEven(const int &i) const;
    bool isPositionValid(const Point &position) const;
    bool isCell(const Point &position) const;
    bool isCorridor(const Point &position) const;
    bool areNeighbours(const Point &first, const Point &second) const;
    bool isWayFree(const Point &first, const Point &second) const;
    Point getIndexCorridor(const Point &first, const Point &second) const;
    std::vector<std::vector<int>> allComponents();
    void labelComponent(int id, std::vector<std::vector<int>> &labels, int x, int y);

    /**
     * Places the two main wall pieces of a wall into the matrix.
     *
     * @param firstHalf the position of the first piece
     * @param secondHalf the position of the second piece
     *
     * @warning Both points are assumed to have *proper matrix indices*
     */
    void placeWallPieces(const Point &firstHalf, const Point &secondHalf);

    /**
     * Places the middle wall piece of a wall into the matrix.
     *
     * @param middlePiece the position of the middle piece
     * @param orientation the orientation of the middle piece
     *
     * @warning the point is assumed to have *proper matrix indices*
     */
    void placeWallMiddlePiece(const Point &middlePiece, const WallOrientation &orientation);

public:
    Board(/* args */);

    /**
     * Checks whether a given position in the matrix is occupied or not.
     *
     * @param position the position to check the occupancy of
     *
     * @warning the position is assumed to have *proper matrix indices*
     */
    bool isFree(const Point &position) const;

    /**
     * Moves a given Player to a new position on the board.
     *
     * @param player the player to move
     * @param cell the new destination of the player
     *
     * @warning the position is assumed to be a *player cell position*
     */
    void movePlayer(std::shared_ptr<Player> player, const Point &cell);

    /**
     * Sets a full wall into the board.
     *
     * @param cell the upper-left corner destination of the wall
     * @param direction the orientation of the new wall
     *
     * @warning the position is assumed to be a *player cell position*
     *
     * @note the orientation of the wall dictates its placement:
     * - if orienation is WallOrientation::Vertical, the wall is placed to the right of cell and continues towards the bottom
     * - if orienation is WallOrientation::Horizontal, the wall is placed under cell and continues towards the right
     */
    void placeWall(const Point &cell, const WallOrientation &direction);

    int getCellSize();

    void debugPrint();

    ~Board();
};
