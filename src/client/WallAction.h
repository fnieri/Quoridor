#pragma once

#include <Player.h>

#include <memory>

// Place a wall somewhere
class WallAction
{
private:
    std::shared_ptr<Board> board;
    std::shared_ptr<Player> player;
    Point destCell; // Position of the cell in the matrix
    WallOrientation orientation;

public:
    WallAction(std::shared_ptr<Board> board, std::shared_ptr<Player> player, const Point &destCell, const WallOrientation &orientation);

    ~WallAction();

    bool isWallPlacementLegal();

    bool isWallPlacementValid();

    void executeAction();
};
