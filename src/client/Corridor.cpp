#include "Corridor.h"
#include "WallEnum.h"

Corridor::Corridor(const WallOrientation &orientation)
    : orientation {orientation}
{
}

void Corridor::placeWall() 
{
    occupied = true;

}

Corridor::~Corridor()
{
}

WallOrientation Corridor::getOrientation()
{
    return orientation;
}