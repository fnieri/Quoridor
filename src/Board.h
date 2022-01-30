#pragma once

#include"PlayerBoard.h"
#include"PlayerAction.h"


class Board
{
private:
    // board contains wall and player board, which will then be displayed
    PlayerBoard playerBoard;
    PlayerAction wallBoard;

public:
    Board(/* args */);
    ~Board();
};
