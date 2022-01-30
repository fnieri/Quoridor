#ifndef WALL_BOARD
#define WALL_BOARD
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


#endif //WALL_BOARD