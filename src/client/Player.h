#pragma once

#include "PlayerEnum.h"
#include "src/common/Point.h"

// defines a player in the game
class Player
{
    int index;
    PawnColors color;
    Point position;
    int nwalls; // how

public:
    Player(const PawnColors &color, const Point &position, const int &nwalls); // Const or not ?
    int x() const;
    int y() const;

    void setPosition(const Point &newPosition);
    void setIndex(int ind);
    void setColor(PawnColors newColor);

    int nWalls() const;
    void takeAwayWall();

    ~Player();
    Point getPosition();
    PawnColors getColor();
    int getIndex();
};
