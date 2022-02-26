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

    /**
     * Check if a point exists in the board
     *
     * @param position the position of a BoardComponent in the matrix
     */
    bool isPositionValid(const Point &position) const;

    /**
     * Check if two points are next to each other in the matrix in a horizontal or vertical direction
     *
     * @param first the position of a Cell
     * @param second the position of a Cell
     *
     * @warning Both points are assumed to have *proper matrix indices*
     */
    bool areNeighbours(const Point &first, const Point &second) const;

    /**
     * Check if two points are next to each other in the board in a diagonal direction
     *
     * @param first the position of a Cell
     * @param second the position of a Cell
     *
     * @warning Both points are assumed to have *proper matrix indices*
     */
    bool areDiagoNeighbours(const Point &first, const Point &second) const;

    /**
     * Check if two cells are not separeted by a wall
     *
     * @param first the position of a Cell
     * @param second the position of a Cell
     *
     * @warning Both points are assumed to have *proper matrix indices*
     * @warning points are assumed to be next to each other
     */
    bool isWayFree(const Point &first, const Point &second) const;

    /**
     * Check if a path is not blocked by walls
     *
     * @note A path in this context means passing a cell to join a cell further away
     *
     * @param current the position of a Cell where the path begins
     * @param overtaken the position of a Cell that is passed
     * @param destination the ending position of a Cell that is joined
     *
     * @warning points are assumed to have *proper matrix indices*
     * @warning the path is assumed to be three cells long
     */
    bool isWayValid(const Point &current, const Point &overtaken, const Point &destination) const;

    /**
     * Give a point that representents the distance between two cells
     *
     * @param first the position of a Cell
     * @param second the position of a Cell
     *
     * @warning points are assumed to have *proper matrix indices*
     */
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

    /**
     * Check if a point corresponds to the location of a cell in the matriw
     *
     * @param position the position to check
     *
     * @warning the position is assumed to have *proper matrix indices*
     */
    bool isCell(const Point &position) const;

    /**
     * Check if a point corresponds to the location of a corridor in the matriw
     *
     * @param position the position to check
     *
     * @warning the position is assumed to have *proper matrix indices*
     */
    bool isCorridor(const Point &position) const;

    /**
     * Check if a number is even
     *
     * @param i the number to check
     */
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
    bool pathExists(const Point &start, FinishLine finishLine) const;

    /**
     * Finds all the players on the board and returns their positions.
     *
     * @return std::vector<Point>
     *
     * @warning the returned point is a *player cell position*
     */
    std::vector<std::shared_ptr<Player>> findPlayers();

    /**
     * Check if the move is of basic type
     *
     * @note basic type means that the player's move is vertical or horizontal
     *
     * @param current the position of the cell where it begins
     * @param destination the position of the cell where it moves
     *
     * @warning the position is assumed to have *proper matrix indices*
     */
    bool isValidBasicMove(const Point &current, const Point &destination) const;

    /**
     * Check if the move is jump type
     *
     * @note jump type means that the player jumps over a cell
     *
     * @param current the position of the cell where it begins
     * @param destination the position of the cell where it moves
     *
     * @warning the position is assumed to have *proper matrix indices*
     */
    bool isValidJumpMove(const Point &current, const Point &destination) const;

    /**
     * Check if the move is of diagonal type
     *
     * @note diagonal type means that the player's move is directed diagonally
     *
     * @param current the position of the cell where it begins
     * @param destination the position of the cell where it moves
     *
     * @warning the position is assumed to have *proper matrix indices*
     */
    bool isValidDiagonalMove(const Point &current, const Point &destination) const;

    /**
     * Checks whether a given Point is on the given finish line.
     *
     * @param position the matrix position to check on
     * @param finishLine the FinishLine to check for
     * @returns bool
     *
     * @warning the point is assumed to have *proper matrix indices*
     */
    bool isPositionOnFinishLine(const Point &position, const FinishLine &finishLine) const;

    int getCellSize();

    void debugPrint();

    ~Board();
};
