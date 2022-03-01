#pragma once

#include "PlayerEnum.h"
#include "../common/Point.h"

// defines a player in the game
class Player
{
    PawnColors color;
    Point position;
    int nwalls; // how

public:
    Player(const PawnColors &color, const Point &position, const int &nwalls); // Const or not ?
    int x() const;
    int y() const;

    void setPosition(const Point &newPosition);

    int nWalls() const;
    void takeAwayWall();

    ~Player();
    Point getPosition();
    PawnColors getColor();
    void setColor(PawnColors newColor);
};
