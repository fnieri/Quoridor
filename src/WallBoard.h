#pragma once

#include<vector>
#include"Wall.h"

class WallBoard
{
private:
    std::vector</*Corridors*/> corridors;
    std::vector<Wall> walls; 
public:
    WallBoard(/* args */);
    ~WallBoard();
};

