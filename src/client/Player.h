#pragma once

#include "PlayerEnum.h"
#include "Point.h"

// defines a player in the game
class Player
{
    PawnColors color;
    Point position;
    int nwalls; // how

public:
    Player(const PawnColors &color, Point &position, int &nwalls); // Const or not ?

    ~Player();
};
