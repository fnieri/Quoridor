#pragma once

#include "PlayerEnum.h"
#include "Point.h"

// defines a player in the game
class Player
{
    PawnColors color;
    Point position;
    int nwalls;
    FinishLine finishLine;
    std::string username;

public:
    Player(const PawnColors &color, const Point &position, const int &nwalls, const FinishLine &finishLine);
    ~Player();

    int x() const;
    int y() const;

    Point getPosition() const;
    Point getMatrixPosition() const;
    std::string getUsername() const;

    void setPosition(const Point &newPosition);
    void setMatrixPosition(const Point &newPosition);

    FinishLine getFinishLine() const;

    int nWalls() const;
    void takeAwayWall();

    PawnColors getColor();
    void setColor(PawnColors newColor);
};
