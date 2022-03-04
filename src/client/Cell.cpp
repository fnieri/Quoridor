/**
 * @file Cell.h
 * @author Nargis, Lèo, Anne-Marie
 * @brief Class representing a Cell in a Board which can be occupied by a Player
 * @date 2022-03-04
 *
 */
#include "Cell.h"

#include <memory>

Cell::Cell(std::shared_ptr<Player> player)
    : player {player}
{
    if (player) {
        occupied = true;
    } else
        occupied = false;
}

void Cell::placePlayer(std::shared_ptr<Player> newPlayer)
{
    player = newPlayer;
    occupied = true;
}

std::shared_ptr<Player> Cell::getPlayer()
{
    return player;
}

void Cell::removePlayer()
{
    player = nullptr;
    occupied = false;
}

PawnColors Cell::getPlayerColor()
{
    if (player)
        return player->getColor();
}

Cell::~Cell()
{
}
