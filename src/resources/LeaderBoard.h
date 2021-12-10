#ifndef LEADER_BOARD
#define LEADER_BOARD


#include"Player.h"


class LeaderBoard
{
private:
    Player player;
    int score;
public:
    LeaderBoard(/* args */);
    void addPlayer();
    /* getLeaderBoard()*/
    ~LeaderBoard();
};


#endif  //LEADER_BOARD