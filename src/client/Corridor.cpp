#include "Corridor.h"
#include "WallEnum.h"

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