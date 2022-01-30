#pragma once



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

