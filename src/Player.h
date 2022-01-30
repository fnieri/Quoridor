#pragma once


#include<string>
#include"PlayerEnum.h"
#include"Point.h"

// defines a player in the game
class Player {
    pawnColors color;
    Point position;
public:
    Player(/* args */);

    void move(std::string action);

    ~Player();
};

