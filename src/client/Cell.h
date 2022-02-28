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
    Cell(std::shared_ptr<Player> player = nullptr);
    ~Cell();

    /**
     * Sets the new Player occupying the cell.
     *
     * @param newPlayer the new Player to occupy the cell
     */
    void placePlayer(std::shared_ptr<Player> newPlayer);

    /**
     * Removes the Player currently occupying the cell.
     */
    void removePlayer();
};
