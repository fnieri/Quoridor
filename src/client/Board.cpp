#include "Board.h"
#include "BoardComponent.h"
#include "Cell.h"
#include "Corridor.h"
#include "Player.h"
#include "Point.h"

#include <iostream>
#include <memory>
#include <stack>

Board::Board()
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

    return isEven(position.x()) && isEven(position.y());
}

bool Board::isCorridor(const Point &position) const
{

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

    Point distance = getDistance(first, second);
    int x = distance.x();
    int y = distance.y();
    return ((x == 2 || x == 0) && (y == 2 || y == 0) && !(x == 2 && y == 2));
}

bool Board::areDiagoNeighbours(const Point &first, const Point &second) const
{

    Point distance = getDistance(first, second);
    return distance.x() == 2 && distance.y() == 2;
}

bool Board::isWayFree(const Point &first, const Point &second) const
{

    Point position = getMiddleBoardComponent(first, second, CORRIDOR);
    if (matrix.at(position.x()).at(position.y()) && isPositionValid(position)) {
        return !matrix.at(position.x()).at(position.y())->isOccupied();
    }

    return false;
}

bool Board::isWayValid(const Point &current, const Point &overtaken, const Point &destination) const
{

    return !isFree(overtaken) && isFree(destination) && isWayFree(current, overtaken) && isWayFree(overtaken, destination);
}

bool Board::isBasicMove(const Point &current, const Point &destination) const
{

    return isPositionValid(destination) && isCell(destination) && areNeighbours(current, destination) && isFree(destination) && isWayFree(current, destination);
}

bool Board::isJumpMove(const Point &current, const Point &destination) const
{

    Point distance = getDistance(current, destination);
    int x = distance.x();
    int y = distance.y();
    Point JumpOver = getMiddleBoardComponent(current, destination, CELL);
    return isPositionValid(destination) && isCell(destination) && ((x == 4 || x == 0) && (y == 4 || y == 0) && !(x == 4 && y == 4))
        && isWayValid(current, JumpOver, destination);
}

bool Board::isDiagonalMove(const Point &current, const Point &destination) const
{

    if (isPositionValid(destination) && isCell(destination) && areDiagoNeighbours(current, destination)) {

        Point vNeighbor {current.x(), destination.y()};
        Point hNeighbor {destination.x(), current.y()};

        return (isPositionValid(vNeighbor) && isWayValid(current, vNeighbor, destination))
            || (isPositionValid(hNeighbor) && isWayValid(current, hNeighbor, destination));
    }

    return false;
}

Point Board::getDistance(const Point &first, const Point &second) const
{

    int x = abs(first.x() - second.x());
    int y = abs(first.y() - second.y());
    Point d {x, y};
    return d;
}

Point Board::getMiddleBoardComponent(const Point &first, const Point &second, const int &shift) const
{

    int x;
    int y;
    // Cells are on the same row
    if (first.y() == second.y()) {
        x = std::max(first.x(), second.x()) - shift;
        y = first.y();
    }
    // Cells are on the same column
    else if (first.x() == second.x()) {
        x = first.x();
        y = std::max(first.y(), second.y()) - shift;
    }
    Point position {x, y};
    return position;
}

void Board::movePlayer(std::shared_ptr<Player> player, const Point &cell)
{
    // We suppose here that the move is valid
    auto matrixPos = player->getMatrixPosition();
    std::dynamic_pointer_cast<Cell>(matrix.at(matrixPos.x()).at(matrixPos.y()))->removePlayer();
    std::dynamic_pointer_cast<Cell>(matrix.at(cell.x()).at(cell.y()))->placePlayer(player);
}

void Board::placeWallPieces(const Point &firstHalf, const Point &secondHalf)
{

    std::dynamic_pointer_cast<Corridor>(matrix[firstHalf.x()][firstHalf.y()])->placeWall();
    std::dynamic_pointer_cast<Corridor>(matrix[secondHalf.x()][secondHalf.y()])->placeWall();
}

void Board::placeWallMiddlePiece(const Point &middlePiece, const WallOrientation &orientation)
{
    // Place the "middle piece" of the wall, on the empty spot in the board
    auto mid = std::make_shared<Corridor>(orientation);
    mid->placeWall();
    matrix.at(middlePiece.x()).at(middlePiece.y()) = mid;
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

bool Board::isPositionOnFinishLine(const Point &position, const FinishLine &finishLine) const
{
    if (!isCell(position))
        return false;

    // define the finish line as Horizontal/Vertical + value for y/x
    bool destinationHorizontal = finishLine == FinishLine::North || finishLine == FinishLine::South;
    int destinationValue = finishLine == FinishLine::North || finishLine == FinishLine::West ? 0 : MATRIX_SIZE - 1;

    // A border is reached and it's the specific finish line
    if ((destinationHorizontal && position.y() == destinationValue) || (!destinationHorizontal && position.x() == destinationValue))
        return true;
    return false;
}

bool Board::pathExists(const Point &start, FinishLine finishLine) const
{
    // This function essentially performs a DFS on the matrix

    Point startMatrix = start * 2;

    // double check the given start position
    if (!isPositionValid(startMatrix))
        return false;

    std::vector<std::vector<bool>> done(MATRIX_SIZE, std::vector<bool>(MATRIX_SIZE));
    std::stack<Point> searches;
    searches.push(startMatrix);

    while (!searches.empty()) {
        Point p = searches.top();
        searches.pop();

        int x = p.x();
        int y = p.y();

        if (done[x][y])
            continue;
        done[x][y] = true;

        // We have found a path to the finish line
        if (isPositionOnFinishLine(Point {x, y}, finishLine))
            return true;

        if (x > 0 && !matrix.at(x - 1).at(y)->isOccupied())
            searches.push(Point {x - 2, y});

        if (x < MATRIX_SIZE - 1 && !matrix.at(x + 1).at(y)->isOccupied())
            searches.push(Point {x + 2, y});

        if (y > 0 && !matrix.at(x).at(y - 1)->isOccupied())
            searches.push(Point {x, y - 2});

        if (y < MATRIX_SIZE - 1 && !matrix.at(x).at(y + 1)->isOccupied())
            searches.push(Point {x, y + 2});
    }

    return false;
}

std::vector<std::shared_ptr<Player>> Board::findPlayers()
{
    std::vector<std::shared_ptr<Player>> players;

    for (int x = 0; x < MATRIX_SIZE; x += 2) {
        for (int y = 0; y < MATRIX_SIZE; y += 2) {
            if (isCell({x, y}) && matrix.at(x).at(y) && matrix.at(x).at(y)->isOccupied()) {
                players.push_back(std::dynamic_pointer_cast<Cell>(matrix.at(x).at(y))->getPlayer());
            }
        }
    }

    return players;
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
            } else if (matrix.at(x).at(y) && matrix.at(x).at(y)->isOccupied()) {
                auto orientation = std::dynamic_pointer_cast<Corridor>(matrix.at(x).at(y))->getOrientation();
                std::cout << (orientation == WallOrientation::Vertical ? "│" : "─");
            } else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}
