#ifndef PLAYER
#define PLAYER

#include<string>
#include"PlayerEnum.h"
#include"Point.h"


class Player
{
private:
    pawnColors color;
    Point position;
public:
    Player(/* args */);
    void move(std::string action);
    ~Player();
};



#endif  //PLAYER