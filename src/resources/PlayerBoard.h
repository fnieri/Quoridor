#ifndef PLAYER_BOARD
#define PLAYER_BOARD
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


#endif  //PLAYER_BOARD