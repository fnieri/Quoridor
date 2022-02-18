#pragma once

#include "BoardComponent.h"
#include "WallEnum.h"

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
