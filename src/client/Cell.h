#pragma once

#include "Player.h"
#include "Point.h"

// contains the information of a cell
class Cell
{
private:
    Point position;
    bool occupied;
    Player *player;

public:
    Cell(/* args */);
    ~Cell();
};
