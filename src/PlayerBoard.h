#pragma once

#include<vector>
#include"Cell.h"


class PlayerBoard
{
private:
    std::vector<Cell> cells;
public:
    PlayerBoard(/* args */);
    ~PlayerBoard();
};

