#include "Board.h"
#include "Player.h"
#include "Point.h"

#include <memory>

Board::Board(/* args */)
{
    // Build the matrix
}

Board::~Board()
{
}

void Board::movePlayer(std::shared_ptr<Player> player, const Point &to)
{
    // to -> are position in the matrix
    //  currentPlayer knows his position
}

void Board::placeWall(const Point &cell, const WallOrientation &direction)
{
    // cell -> is a position in the matrix
}