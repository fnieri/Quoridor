#pragma once

#include "BoardComponent.h"
#include "WallEnum.h"
#include "Point.h"
#include "Player.h"

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
    const int CELL = 2;
    const int CORRIDOR = 1;

    bool isPositionValid(const Point &position) const;
    bool areNeighbours(const Point &first, const Point &second) const;
    bool areDiagoNeighbours(const Point &first, const Point &second) const;
    bool isWayFree(const Point &first, const Point &second) const;
    bool isWayValid(const Point &current, const Point &overtaken, const Point &destination) const;
    Point getMiddleBoardComponent(const Point &first, const Point &second, const int &shift) const;
    Point getDistance(const Point &first, const Point &second) const;
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
    Board();

    bool isCell(const Point &position) const;
    bool isCorridor(const Point &position) const;
    bool isEven(const int &i) const;

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
     * DO NOT CALL THIS FUNCTION DIRECTLY!
     * Create a PlayerAction and call PlayerAction::executeAction() instead.
     *
     * @param player the Player to move
     * @param cell the new destination of the Player
     *
     * @warning the position is assumed to be a *player cell position*
     */
    void movePlayer(std::shared_ptr<Player> player, const Point &cell);

    /**
     * Sets a full wall into the board.
     * DO NOT CALL THIS FUNCTION DIRECTLY!
     * Create a WallAction and call WallAction::executeAction() instead.
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

    /**
     * Finds whether a path from a starting point to one of the board borders exists.
     *
     * @param start the starting point for the pathfinding
     * @param finishLine the board border for pathfind to
     * @return bool
     *
     * @warning the position is assumed to be a *player cell position*
     *
     * @note The accepted values for finishLine are:
     * - 0=north
     * - 1=east
     * - 2=south
     * - 3=west
     */
    bool pathExists(const Point &start, int finishLine) const;

    /**
     * Finds all the players on the board and returns their positions.
     *
     * @return std::vector<Point>
     *
     * @warning the returned point is a *player cell position*
     */
    std::vector<std::shared_ptr<Player>> findPlayers();

    bool isBasicMove(const Point &current, const Point &destination) const;
    bool isJumpMove(const Point &current, const Point &destination) const;
    bool isDiagonalMove(const Point &current, const Point &destination) const;

    int getCellSize();

    void debugPrint();

    ~Board();
};
