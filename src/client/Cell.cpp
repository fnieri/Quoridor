#include "Cell.h"

#include <memory>

Cell::Cell(std::shared_ptr<Player> player)
    : player {player}
{
}

Cell::~Cell()
{
}
