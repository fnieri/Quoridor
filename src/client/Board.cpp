#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "Cell.h"
#include "Corridor.h"

#include <memory>

Board::Board(/* args */)
{
    for (int x=0; x < MATRIX_SIZE; x++) 
    {
        matrix.push_back({});
        for (int y=0; y < MATRIX_SIZE; y++) 
        {
            if (isCell({x,y})) 
            {
                matrix[x].push_back(std::make_shared<Cell>());
            }
            else if (isCorridor({x,y}))
            {
                if (isEven(x))
                {
                    matrix[x].push_back(std::make_shared<Corridor>(WallOrientation::Vertical));
                }
                else 
                    matrix[x].push_back(std::make_shared<Corridor>(WallOrientation::Horizontal));
            }
            else
                matrix[x].push_back(nullptr); 
        }
    }
}

Board::~Board()
{
}

bool Board::isEven(const int &i) const 
{
    return ( ( i % 2 ) == 0);
}

bool Board::isPositionValid(const Point &position) const
{
    return  position.x() >= 0 && position.x() < MATRIX_SIZE && position.y() >= 0 && position.y() < MATRIX_SIZE;
}

bool Board::isCell(const Point &position) const 
{
    // Is this a cell emplacement ?
    return isEven(position.x()) && isEven(position.y());
}

bool Board::isCorridor(const Point &position) const 
{
    // Is this a corridor emplacement ?
    return isEven(position.x()) || isEven(position.y());
}

bool Board::isFree(const Point &position) const
{
    return !matrix[position.x()][position.y()]->isOccupied();
}

bool Board::areNeighbours(const Point &first, const Point &second) const 
{
    // This wroks with up down left right. Ask myself : does this works with diagonal ? i think yes
    // For diagonal to work distX == 2 && distY == 2
    int distX = abs(first.x() - second.x());
    int distY = abs(first.y() - second.y());
    return ((distX == 2 || distX == 0) && (distY == 2 || distY == 0));
}

bool Board::isWayFree(const Point &first, const Point &second) const 
{

    // Check if two cells are separated by a wall
    Point position = getIndexCorridor(first, second);
    if (matrix[position.x()][position.y()] && isPositionValid(position)) 
    {
        return !matrix[position.x()][position.y()]->isOccupied();
    }
}

Point Board::getIndexCorridor(const Point &first, const Point &second) const
{
    // Give the position in the matrix of a Corridor between two Cells
    int x;
    int y;
    // Cells are on the same row
    if (first.x() == second.x()) 
    {
        x = first.x();
        y = std::max(first.y(), second.y()) - 1;
            
    }
    // Cells are on the same column
    else if (first.y() == second.y())
    {
        x = std::max(first.x(), second.x()) -1;
        y = first.y();
    }

    Point position{x,y};
    return position;

}

void Board::movePlayer(std::shared_ptr<Player> player, const Point &to)
{
    // We suppose here that the move is valide
    std::dynamic_pointer_cast<Cell>(matrix[player->x()][player->y()])->removePlayer();
    std::dynamic_pointer_cast<Cell>(matrix[to.x()][to.y()])->placePlayer(player);
}

void Board::placeWallPieces(const Point &firstHalf, const Point &secondHalf)
{
    // We suppose here that the the placement of the wall is valide
    // We suppose here that firstHalf and secondHalf have already been converted into matrix indexes
    // Downcasting
    std::dynamic_pointer_cast<Corridor>(matrix[firstHalf.x()][firstHalf.y()])->placeWall();
    std::dynamic_pointer_cast<Corridor>(matrix[secondHalf.x()][secondHalf.y()])->placeWall();
}

void Board::placeWall(const Point &cell, const WallOrientation &direction)
{
    // cell -> is a position in the matrix
}

std::vector<std::vector<int>> Board::allComponents() 
{
    // Build the matrix of all the connected component 
    int id = 0;
    std::vector<std::vector<int>> labels(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 0));
    for (int x=0; x < MATRIX_SIZE; x+=2)   
    {
        for(int y=0; y < MATRIX_SIZE; y+=2) 
        {
            if (labels[x][y] == 0) 
            { 
                id +=1;
                labelComponent(id, labels, x, y);
            }
        }
    }
    return labels;
}

void Board::labelComponent(int id, std::vector<std::vector<int>> &labels, int x, int y) 
{   
    // Build each connected component
    labels[x][y] = id;
    std::vector<Point> shifts = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};  // UP, DOWN, LEFT, RIGHT
    for (auto &shift: shifts)
    {
        int x_shift = x + shift.x();
        int y_shift = y + shift.y();
        if (isPositionValid({x_shift, y_shift})) 
        {
            if (isWayFree({x,y}, {x_shift, y_shift})  && labels[x_shift][y_shift] == 0) 
            {
                labelComponent(id, labels, x_shift, y_shift);
            }
        }
    }
}


int Board::getCellSize()
{
    return CELL_SIZE;
}