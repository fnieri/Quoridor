#pragma once

#include"Point.h"
#include"Player.h"

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

