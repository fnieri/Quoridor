#ifndef BOARD
#define BOARD
#include"PlayerBoard.h"
#include"PlayerAction.h"


class Board
{
private:
    PlayerBoard playerboard;
    PlayerAction wallBoard;

public:
    Board(/* args */);
    ~Board();
};


#endif //BOARD