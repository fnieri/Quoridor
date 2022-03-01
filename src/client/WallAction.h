#pragma once

#include "../common/Serializable.h"
#include "Board.h"
#include "Player.h"
#include "WallEnum.h"
#include <nlohmann/json.hpp>

#include <memory>

// Place a wall somewhere
class WallAction : public Serializable
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

    /**
     * @brief Return serialized json of a WallAction as such
     *
     * {
     *  wall_cell : {
     *    x : 0,
     *    y : 0
     *    }
     *  wall_orientation
     * }
     *
     * @return nlohmann::json
     */
    nlohmann::json serialized();
};
