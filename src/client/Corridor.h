#pragma once

#include "BoardComponent.h"

class Corridor : public BoardComponent
{
private:
    WallOrientation orientation;

public:
    Corridor(const WallOrientation &orientation);
    void placeWall();
    ~Corridor();
    WallOrientation getOrientation();
};
