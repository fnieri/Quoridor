#pragma once

#include<tuple>
#include"Point.h"


class Wall
{
private:
    std::tuple<Point> position;    
public:
    Wall(/* args */);
    ~Wall();
};

