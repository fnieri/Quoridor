#pragma once

#include "Board.h"
#include "Player.h"
#include "PlayerEnum.h"
#include "Point.h"

#include <nlohmann/json.hpp>

#include <memory>
#include <string>

class PlayerAction
// For moving a player
{
    std::shared_ptr<Board> board;
    std::shared_ptr<Player> player;

    /// Is a position in the board matrix
    Point destination;

public:
    PlayerAction(std::shared_ptr<Board> board, std::shared_ptr<Player> player, const Point &_destination);

    ~PlayerAction();

    /**
     * Check if the move of the player is valid
     */
    bool isActionValid();

    /**
     * Check if we have a winner
     */
    bool isGameOver();

    /**
     * Make the move
     */
    bool executeAction();

    nlohmann::json serialized();
};
