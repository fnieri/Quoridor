#ifndef PLAYER_ACTION
#define PLAYER_ACTION


#include<string>
#include"PlayerEnum.h"


class PlayerAction {
    std::string playerAction;
public:
    PlayerAction(/* args */);

    ~PlayerAction();

    bool isActionValid();

    bool isGameOver();
};


#endif //PLAYER_ACTION
