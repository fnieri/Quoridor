#pragma once

#include "Point.h"
#include <tuple>

class Wall
{
private:
    std::tuple<Point> position;

public:
    Wall(/* args */);
    ~Wall();
};
