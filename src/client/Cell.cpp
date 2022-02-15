#include "Cell.h"

#include <memory>

Cell::Cell(std::shared_ptr<Player> player)
    : player {player}
{
    if (player) 
    {
        occupied = true;
    }
    else 
        occupied = false;
}

void Cell::placePlayer(std::shared_ptr<Player> newPlayer) 
{
    player = newPlayer;
    occupied = true;
}

void Cell::removePlayer() 
{
    player = nullptr;
    occupied = false;
}

Cell::~Cell()
{
}
