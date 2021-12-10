#ifndef CELL
#define CELL
#include"Point.h"
#include"Player.h"


class Cell
{
private:
    Point position;
    bool occupied;
    Player *player;

public:
    Cell(/* args */);
    ~Cell();
};


#endif  // CELL