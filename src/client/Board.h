#pragma once

#include "BoardComponent.h"
#include "WallEnum.h"

#include <memory>
#include <vector>

class Board
{
private:
    std::vector<std::vector<std::shared_ptr<BoardComponent>>> matrix; // Question ? : probably gonna use shared_ptr
    const int SIZE = 17;

public:
    Board(/* args */);
    void movePlayer(std::shared_ptr<Player> player, const Point &to);
    void placeWall(const Point &cell, const WallOrientation &direction);

    ~Board();
};
