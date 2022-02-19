#pragma once

#include "Board.h"
#include "Player.h"
#include "WallEnum.h"

#include <nlohmann/json.hpp>

#include <memory>

// Place a wall somewhere
class WallAction
{
private:
    std::shared_ptr<Board> board;
    std::shared_ptr<Player> player;
    Point destCell; // Position of the cell from the view of the player
    WallOrientation orientation;

public:
    WallAction(std::shared_ptr<Board> board, std::shared_ptr<Player> player, const Point &destCell, const WallOrientation &orientation);

    ~WallAction();

    bool isWallPlacementLegal();

    bool isWallPlacementValid();

    bool executeAction();

    nlohmann::json serialized();
};
