#include "Corridor.h"

Corridor::Corridor(const WallOrientation &orientation)
    : orientation {orientation}
{
}

Corridor::~Corridor()
{
}

WallOrientation Corridor::getOrientation()
{
    return orientation;
}