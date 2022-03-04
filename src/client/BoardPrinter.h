
#pragma once

#include "Board.h"
#include "Player.h"

// Prints the board to the console
class BoardPrinter
{
private:
    Board board;
    Player player;

public:
    BoardPrinter(/* args */);
    ~BoardPrinter();
    void printBoard();
};
