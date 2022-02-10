#pragma once

#include "Wall.h"
#include <vector>

class WallBoard
{
private:
    std::vector</*Corridors*/> corridors;
    std::vector<Wall> walls;

public:
    WallBoard(/* args */);
    ~WallBoard();
};
