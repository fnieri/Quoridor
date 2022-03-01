#pragma once

#include "../common/Serializable.h"
#include "Board.h"
#include "Player.h"
#include "PlayerEnum.h"
#include "../common/Point.h"
#include <nlohmann/json.hpp>

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

    nlohmann::json serialized();
};
