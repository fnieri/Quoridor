/**
* @file Cell.h
* @author Nargis, Lèo, Anne-Marie
* @brief Class representing a Cell in a Board which can be occupied by a Player
* @date 2022-03-04
*
*/

#pragma once

#include "BoardComponent.h"
#include "Player.h"

#include <memory>

/**
 * Subclass of BoardComponent and used to indicate the presence of a player in the Board.
 */
class Cell : public BoardComponent
{
private:
    /**
     * The Player currently occupying the cell.
     * Is set to nullptr if unoccupied.
     */
    std::shared_ptr<Player> player;

public:
    /**
     * Construct a new Cell object.
     *
     * @param player the player occupying that cell, if any
     */
    Cell(std::shared_ptr<Player> player = nullptr);
    ~Cell();

    /**
     * Sets the new Player occupying the cell.
     *
     * @param newPlayer the new Player to occupy the cell
     */
    void placePlayer(std::shared_ptr<Player> newPlayer);

    /**
     * Returns the Player currently occupying the cell.
     *
     * @returns std::shared_ptr<Player>
     */
    std::shared_ptr<Player> getPlayer();
    PawnColors getPlayerColor();
    /**
     * Removes the Player currently occupying the cell.
     */
    void removePlayer();
};
