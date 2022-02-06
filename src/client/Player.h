#pragma once

#include "PlayerEnum.h"
#include "Point.h"
#include <string>

// defines a player in the game
class Player
{
    pawnColors color;
    Point position;

public:
    Player(/* args */);

    void move(std::string action);

    ~Player();
};
