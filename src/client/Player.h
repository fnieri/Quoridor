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
    Player(const PawnColors &color, const Point &position, const int &nwalls); // Const or not ?
    ~Player();

    int x() const;
    int y() const;

    Point getPosition() const;
    Point getMatrixPosition() const;

    void setPosition(const Point &newPosition);
    void setMatrixPosition(const Point &newPosition);

    int nWalls() const;
    void takeAwayWall();

    PawnColors getColor();
    void setColor(PawnColors newColor);
};
