/**
 * @file Player.h
 * @author Nargis, Lèo, Anne-Marie
 * @brief Class representing a Player in a game
 * @date 2022-03-04
 *
 */
#pragma once

#include "PlayerEnum.h"
#include "src/common/Point.h"

/**
 * Represents a Player in the game.
 *
 */
class Player
{
    /// The color of the Player, used to uniquely identify players in a game.
    PawnColors color;

    /**
     * The current position of the Player on the Board.
     *
     * @warning represents a *player cell position*
     */
    Point position;

    /// The number of walls still available for the Player to place on the Board.
    int nwalls;

    /// The finish line of the Player. They win when they reach this border.
    FinishLine finishLine;

    /// The username of the Player.
    std::string username;

    int index;

public:
    /**
     * Construct a new Player
     *
     * @param color the unique color of the player
     * @param position the starting position on the Board
     * @param nwalls the starting number of walls
     * @param finishLine the finish line objective of the player
     */
    Player(const PawnColors &color, const Point &position, const int &nwalls, const FinishLine &finishLine, const std::string &username);
    ~Player();

    /// Returns the x cell position
    int x() const;
    /// Returns the y cell position
    int y() const;

    /**
     * Sets the current position of the Player on the game Board.
     *
     * @param newPosition the new position
     *
     * @warning the given position is assumed to be a *player cell position*
     */
    void setPosition(const Point &newPosition);

    /**
     * Sets the current position of the Player given the Board matrix position.
     *
     * @param newPosition the new position in the matrix
     *
     * @warning the given position is assumed to be a *proper matrix position*
     */
    void setMatrixPosition(const Point &newPosition);

    /**
     * Return the current position of the Player.
     *
     * @returns Point
     *
     * @warning the returned position is a *player cell position*
     */
    Point getPosition() const;

    /**
     * Return the current position in the board matrix.
     *
     * @returns Point
     *
     * @warning the returned position is a *proper matrix position*
     */
    Point getMatrixPosition() const;

    /**
     * Returns the Player's username.
     *
     * @returns std::string
     */
    std::string getUsername() const;

    /**
     * Returns the Player's finish line.
     *
     * @returns FinishLine
     */
    FinishLine getFinishLine() const;

    /**
     * Returns the number of walls remaining to the Player.
     *
     * @returns int
     */
    int nWalls() const;

    /**
     * Decrements one wall from the Player.
     *
     */
    void takeAwayWall();

    /**
     * Returns the Player's color.
     *
     * @returns PawnColors
     */
    PawnColors getColor();

    /**
     * Sets the Player's color.
     *
     * @param newColor the new pawn color for the player.
     */
    void setColor(PawnColors newColor);

    
    int getIndex();
    void setIndex(int ind);

};