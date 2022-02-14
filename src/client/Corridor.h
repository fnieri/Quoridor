#pragma once

#include "BoardComponent.h"

class Corridor : public BoardComponent
{
private:
    WallOrientation orientation;

public:
    Corridor(const WallOrientation &orientation);
    ~Corridor();
    WallOrientation getOrientation();
};
