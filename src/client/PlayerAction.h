#pragma once

#include "Board.h"
#include "Player.h"
#include "PlayerEnum.h"
#include "Point.h"

#include <memory>
#include <string>

class PlayerAction
// For moving a player
{
    std::shared_ptr<Board> board;
    std::shared_ptr<Player> player;
    Point destination;

public:
    PlayerAction(std::shared_ptr<Board> board, std::shared_ptr<Player> player, const Point &destination); // Question ? pointer or reference

    ~PlayerAction();

    bool isActionValid();

    bool isGameOver();

    bool executeAction();
};
