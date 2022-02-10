#pragma once

#include "PlayerEnum.h"
#include <string>

class PlayerAction
{
    std::string playerAction;

public:
    PlayerAction(/* args */);

    ~PlayerAction();

    bool isActionValid();

    bool isGameOver();
};
