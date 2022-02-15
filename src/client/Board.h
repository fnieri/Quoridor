#pragma once

#include "BoardComponent.h"
#include "WallEnum.h"
#include "Point.h"
#include "Player.h"

#include <memory>
#include <vector>

class Board
{
private:
    std::vector<std::vector<std::shared_ptr<BoardComponent>>> matrix; 

    const int CELL_SIZE = 9;
    const int MATRIX_SIZE = (CELL_SIZE * 2) - 1;
    bool isEven(const int &i) const;
    bool isPositionValid(const Point &position) const;
    bool isCell(const Point &position) const;
    bool isCorridor(const Point &position) const;
    bool areNeighbours(const Point &first, const Point &second) const;
    bool isWayFree(const Point &first, const Point &second) const;
    Point getIndexCorridor(const Point &first, const Point &second) const;

public:
    Board(/* args */);
    bool isFree(const Point &position) const;
    void movePlayer(std::shared_ptr<Player> player, const Point &to);
    void placeWall(const Point &cell, const WallOrientation &direction);
    void placeWallPieces(const Point &firstHalf, const Point &secondHalf);

    int getCellSize();

    ~Board();
};
