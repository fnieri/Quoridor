#ifndef BOARD_PRINTER
#define BOARD_PRINTER
#include"Board.h"
#include"Player.h"

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


#endif  // BOARDPRINTER