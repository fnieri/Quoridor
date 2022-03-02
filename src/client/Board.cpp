#include "Board.h"
#include "BoardComponent.h"
#include "Cell.h"
#include "Corridor.h"
#include "Player.h"
#include "src/common/Point.h"


#include <iostream>
#include <memory>

using json = nlohmann::json;

Board::Board(/* args */)
{
    for (int x = 0; x < MATRIX_SIZE; x++) {
        matrix.push_back({});
        for (int y = 0; y < MATRIX_SIZE; y++) {
            if (isCell({x, y})) {
                matrix[x].push_back(std::make_shared<Cell>());
            } else if (isCorridor({x, y})) {
                if (isEven(x)) {
                    matrix[x].push_back(std::make_shared<Corridor>(WallOrientation::Horizontal));
                } else
                    matrix[x].push_back(std::make_shared<Corridor>(WallOrientation::Vertical));
            } else
                matrix[x].push_back(nullptr);
        }
    }
}

Board::~Board()
{
}

bool Board::isEven(const int &i) const
{
    return ((i % 2) == 0);
}

bool Board::isPositionValid(const Point &position) const
{
    return position.x() >= 0 && position.x() < MATRIX_SIZE && position.y() >= 0 && position.y() < MATRIX_SIZE;
}

bool Board::isCell(const Point &position) const
{
    // Is this a cell emplacement ?
    return isEven(position.x()) && isEven(position.y());
}

bool Board::isCorridor(const Point &position) const
{
    // Is this a corridor emplacement ?
    // Here != serves as a xor, since indices where both are even are cells and where both are odd are empty
    return isEven(position.x()) != isEven(position.y());
}

bool Board::isFree(const Point &position) const
{
    auto component = matrix.at(position.x()).at(position.y());
    if (component) {
        return !component->isOccupied();
    }
    return true;
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
    if (matrix[position.x()][position.y()] && isPositionValid(position)) {
        return !matrix[position.x()][position.y()]->isOccupied();
    }

    return false;
}

Point Board::getIndexCorridor(const Point &first, const Point &second) const
{
    // Give the position in the matrix of a Corridor between two Cells
    int x;
    int y;
    // Cells are on the same row
    if (first.x() == second.x()) {
        x = first.x();
        y = std::max(first.y(), second.y()) - 1;

    }
    // Cells are on the same column
    else if (first.y() == second.y()) {
        x = std::max(first.x(), second.x()) - 1;
        y = first.y();
    }

    Point position {x, y};
    return position;
}

void Board::movePlayer(std::shared_ptr<Player> player, const Point &cell)
{
    // We suppose here that the move is valid
    // std::dynamic_pointer_cast<Cell>(matrix[player->x()][player->y()])->removePlayer();
    // std::dynamic_pointer_cast<Cell>(matrix[to.x()][to.y()])->placePlayer(player);
    // TODO: Needs fixing
}

void Board::placeWallPieces(const Point &firstHalf, const Point &secondHalf)
{
    // We suppose here that the the placement of the wall is valid
    // We suppose here that the given indices have already been converted into matrix indexes
    // Downcasting
    std::dynamic_pointer_cast<Corridor>(matrix[firstHalf.x()][firstHalf.y()])->placeWall();
    std::dynamic_pointer_cast<Corridor>(matrix[secondHalf.x()][secondHalf.y()])->placeWall();
}

void Board::placeWallMiddlePiece(const Point &middlePiece, const WallOrientation &orientation)
{
    // Place the "middle piece" of the wall, on the empty spot in the board
    auto mid = std::make_shared<Corridor>(orientation);
    mid->placeWall();
    matrix[middlePiece.x()][middlePiece.y()] = mid;
}

void Board::placeWall(const Point &cell, const WallOrientation &direction)
{
    // cell -> is a position from the the view of the player, must be converted to matrix index first
    // Wall placement is assumed to be valid, but index checks are still done for security

    if (cell.x() < 0 || cell.y() < 0 || cell.x() >= CELL_SIZE - 1 || cell.y() >= CELL_SIZE - 1)
        // Here CELL_SIZE-1 is used since you can't place walls on the last row/column
        return;

    int x = cell.x() * 2;
    int y = cell.y() * 2;

    // Place the wall pieces, either vertically or horizontally, then the middle piece
    if (direction == WallOrientation::Vertical) {
        placeWallPieces(Point {x + 1, y}, Point {x + 1, y + 2});
    } else {
        placeWallPieces(Point {x, y + 1}, Point {x + 2, y + 1});
    }
    placeWallMiddlePiece(Point {x + 1, y + 1}, direction);
}

std::vector<std::vector<int>> Board::allComponents()
{
    // Build the matrix of all the connected component
    int id = 0;
    std::vector<std::vector<int>> labels(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 0));
    for (int x = 0; x < MATRIX_SIZE; x += 2) {
        for (int y = 0; y < MATRIX_SIZE; y += 2) {
            if (labels[x][y] == 0) {
                id += 1;
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
    std::vector<Point> shifts = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}}; // UP, DOWN, LEFT, RIGHT
    for (auto &shift : shifts) {
        int x_shift = x + shift.x();
        int y_shift = y + shift.y();
        if (isPositionValid({x_shift, y_shift})) {
            if (isWayFree({x, y}, {x_shift, y_shift}) && labels[x_shift][y_shift] == 0) {
                labelComponent(id, labels, x_shift, y_shift);
            }
        }
    }
}

int Board::getCellSize()
{
    return CELL_SIZE;
}

void Board::debugPrint()
{
    for (int y = 0; y < MATRIX_SIZE; y++) {
        for (int x = 0; x < MATRIX_SIZE; x++) {
            if (isCell({x, y})) {
                std::cout << "■";
            } else if (matrix[x][y] && matrix[x][y]->isOccupied()) {
                auto orientation = std::dynamic_pointer_cast<Corridor>(matrix[x][y])->getOrientation();
                std::cout << (orientation == WallOrientation::Vertical ? "│" : "─");
            } else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

json Board::serialized()
{
}
