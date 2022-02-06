#pragma once

#include "Cell.h"
#include <vector>

class PlayerBoard
{
private:
    std::vector<Cell> cells;

public:
    PlayerBoard(/* args */);
    ~PlayerBoard();
};
