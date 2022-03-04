/**
* @file Corridor.h
* @author Nargis, Lèo, Anne-Marie
* @brief Class representing a Corridor in a Board which can be occupied by a Wall
* @date 2022-03-04
*
*/

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

void Corridor::setOrientation(WallOrientation _orientation)
{
    orientation = _orientation;
}

WallOrientation Corridor::getOrientation()
{
    return orientation;
}