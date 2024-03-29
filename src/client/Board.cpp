/**
 * @file Board.cpp
 * @author Nargis, Lèo, Anne-Marie, Francesco
 * @brief Class representing a Board in a game
 * @date 2022-03-04
 *
 */

#include "Board.h"
#include "BoardComponent.h"
#include "Cell.h"
#include "Corridor.h"
#include "Player.h"
#include "src/common/Point.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <memory>
#include <stack>

using json = nlohmann::json;

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
    return ((x == 2 || x == 0) && (y == 2 || y == 0) && x != y);
}

bool Board::areDiagoNeighbours(const Point &first, const Point &second) const
{

    Point distance = getDistance(first, second);
    return distance.x() == 2 && distance.y() == 2;
}

bool Board::isWayFree(const Point &first, const Point &second) const
{
    int x;
    int y;
    if (first.y() == second.y()) {
        // Cells are on the same row
        x = std::max(first.x(), second.x()) - 1;
        y = first.y();
    } else if (first.x() == second.x()) {
        // Cells are on the same column
        x = first.x();
        y = std::max(first.y(), second.y()) - 1;
    } else {
        return false;
    }

    if (matrix.at(x).at(y) && isPositionValid(Point {x, y})) {
        return !matrix.at(x).at(y)->isOccupied();
    }

    return false;
}

bool Board::isWayValid(const Point &current, const Point &overtaken, const Point &destination) const
{

    return !isFree(overtaken) && isFree(destination) && isWayFree(current, overtaken) && isWayFree(overtaken, destination);
}

bool Board::isValidBasicMove(const Point &current, const Point &destination) const
{

    return isPositionValid(destination) && isCell(destination) && areNeighbours(current, destination) && isFree(destination) && isWayFree(current, destination);
}

bool Board::isValidJumpMove(const Point &current, const Point &destination) const
{

    Point distance = getDistance(current, destination);
    int dx = distance.x();
    int dy = distance.y();

    if (!((dx == 4 || dx == 0) && (dy == 4 || dy == 0) && (dx != dy)))
        return false;

    int x;
    int y;
    if (current.y() == destination.y()) {
        // Cells are on the same row
        x = std::max(current.x(), destination.x()) - 2;
        y = current.y();
    } else if (current.x() == destination.x()) {
        // Cells are on the same column
        x = current.x();
        y = std::max(current.y(), destination.y()) - 2;
    } else {
        return false;
    }

    return isPositionValid(destination) && isCell(destination) && isWayValid(current, Point {x, y}, destination);
}

bool Board::isValidDiagonalMove(const Point &current, const Point &destination) const
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

void Board::movePlayer(std::shared_ptr<Player> player, const Point &cell)
{
    // We suppose here that the move is valid
    auto matrixPos = player->getMatrixPosition();
    std::dynamic_pointer_cast<Cell>(matrix.at(matrixPos.x()).at(matrixPos.y()))->removePlayer();
    std::dynamic_pointer_cast<Cell>(matrix.at(cell.x()).at(cell.y()))->placePlayer(player);
}

void Board::spawnPlayer(std::shared_ptr<Player> player)
{
    auto matrixPos = player->getMatrixPosition();
    std::dynamic_pointer_cast<Cell>(matrix.at(matrixPos.x()).at(matrixPos.y()))->placePlayer(player);
}

void Board::removePlayer(std::shared_ptr<Player> player)
{
    auto matrixPos = player->getMatrixPosition();
    std::dynamic_pointer_cast<Cell>(matrix.at(matrixPos.x()).at(matrixPos.y()))->removePlayer();
}

void Board::placeWallPieces(const Point &firstHalf, const Point &secondHalf)
{
    std::dynamic_pointer_cast<Corridor>(matrix.at(firstHalf.x()).at(firstHalf.y()))->placeWall();
    std::dynamic_pointer_cast<Corridor>(matrix.at(secondHalf.x()).at(secondHalf.y()))->placeWall();
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

bool Board::pathExists(const Point &start, FinishLine finishLine, Point newWallPiece1, Point newWallPiece2) const
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

        if (x > 0 && !matrix.at(x - 1).at(y)->isOccupied() && Point {x - 1, y} != newWallPiece1 && Point {x - 1, y} != newWallPiece2)
            searches.push(Point {x - 2, y});

        if (x < MATRIX_SIZE - 1 && !matrix.at(x + 1).at(y)->isOccupied() && Point {x + 1, y} != newWallPiece1 && Point {x + 1, y} != newWallPiece2)
            searches.push(Point {x + 2, y});

        if (y > 0 && !matrix.at(x).at(y - 1)->isOccupied() && Point {x, y - 1} != newWallPiece1 && Point {x, y - 1} != newWallPiece2)
            searches.push(Point {x, y - 2});

        if (y < MATRIX_SIZE - 1 && !matrix.at(x).at(y + 1)->isOccupied() && Point {x, y + 1} != newWallPiece1 && Point {x, y + 1} != newWallPiece2)
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
    auto m = getRotatedBoardMatrix(FinishLine::North);
    auto players = findPlayers();

    for (int y = 0; y < MATRIX_SIZE; y++) {
        for (int x = 0; x < MATRIX_SIZE; x++) {
            int isPlayer = false;
            for (auto &player : players) {
                if (player->getPosition()*2 == Point {x, y}) {
                    isPlayer = true;
                    break;
                }
            }
            if (isPlayer) {
                std::cout << "X";
            } else if (isCell({x, y})) {
                std::cout << ".";
            } else if (m.at(x).at(y) && m.at(x).at(y)->isOccupied()) {
                auto orientation = std::dynamic_pointer_cast<Corridor>(m.at(x).at(y))->getOrientation();
                std::cout << (orientation == WallOrientation::Vertical ? "│" : "─");
            } else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

Point Board::getRotatedMatrixPosition(Point p, FinishLine f, bool invert)
{
    if (invert) {
        // Invert the rotation if requested
        // North doesn't need changing at all, South is the inverse of itself,
        // and East/West are the inverse of each other, so swap them around
        if (f == FinishLine::East)
            f = FinishLine::West;
        else if (f == FinishLine::West)
            f = FinishLine::East;
    }

    switch (f) {
    case FinishLine::South:
        return Point {MATRIX_SIZE - p.x() - 1, MATRIX_SIZE - p.y() - 1};

    case FinishLine::East:
        return Point {p.y(), MATRIX_SIZE - p.x() - 1};

    case FinishLine::West:
        return Point {MATRIX_SIZE - p.y() - 1, p.x()};

    case FinishLine::North:
    default:
        return p;
    }
}

std::vector<std::vector<std::shared_ptr<BoardComponent>>> Board::getRotatedBoardMatrix(FinishLine rotation)
{
    auto rotated = matrix;

    for (int x = 0; x < MATRIX_SIZE; x++) {
        for (int y = 0; y < MATRIX_SIZE; y++) {
            // copy over all the board components while rotating the matrix
            Point p = getRotatedMatrixPosition(Point {x, y}, rotation, false);
            rotated.at(p.x()).at(p.y()) = matrix.at(x).at(y);

            // make sure to rotate the direction of the walls when needed
            /* if ((rotation == FinishLine::East || rotation == FinishLine::West) && rotated.at(p.x()).at(p.y()) && !isCell(p)) { */
            /*     auto wall = std::dynamic_pointer_cast<Corridor>(rotated.at(p.x()).at(p.y())); */

            /*     wall->setOrientation(wall->getOrientation() == WallOrientation::Horizontal ? WallOrientation::Vertical : WallOrientation::Horizontal); */
            /* } */
        }
    }

    return rotated;
}

auto Board::getSerializedWalls() -> json
{
    auto wallPos(json::array());

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {

            auto comp {matrix.at(i).at(j)};
            auto position {
                Point {i, j}
            };

            if (comp && comp->isOccupied() && !isCell(position)) {

                auto orientation {std::dynamic_pointer_cast<Corridor>(comp)->getOrientation()};

                wallPos.push_back({
                    {"orientation", orientation          },
                    {"position",    position.serialized()},
                });
            }
        }
    }

    return wallPos;
}

auto Board::putSerializedWalls(json wallPos) -> void
{
    for (auto &i_wall : wallPos) {

        auto ori {static_cast<WallOrientation>(i_wall["orientation"])};
        auto pos {Point::deserialized(i_wall["position"].dump())};

        auto corridor {std::make_shared<Corridor>(ori)};
        corridor->placeWall();

        matrix.at(pos.x()).at(pos.y()) = corridor;
    }
}

json Board::serialized()
{
    json wallArray = json::array(), playerArray = json::array();
    int NOfPlayers = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix.at(i).at(j)) { // Check if current looped boardComponent is non nullptr
                if (matrix.at(i).at(j)->isOccupied()) { // Someone or a wall is in a corridor
                    if (isCorridor({i, j})) {

                        WallOrientation wallOrientation = std::dynamic_pointer_cast<Corridor>(matrix.at(i).at(j))->getOrientation();
                        json wallJson = {{"wall_orientation", toJsonOutput(wallOrientation)}, {"wall_position", Point {i, j}.serialized()}};
                        wallArray.push_back(wallJson);

                    }
                    // Case where the cell is occupied by a Player
                    else if (isCell({i, j})) {
                        NOfPlayers++;
                        std::shared_ptr<Player> currentPlayer = std::dynamic_pointer_cast<Cell>(matrix.at(i).at(j))->getPlayer();
                        // Get informations about player and serialize it
                        PawnColors currentPlayerColor = currentPlayer->getColor();
                        int currentPlayerNWalls = currentPlayer->nWalls();
                        std::string currentPlayerUsername = currentPlayer->getUsername();
                        FinishLine currentFinishLine = currentPlayer->getFinishLine();
                        json playerJson = {{"player_id", static_cast<int>(currentPlayerColor)}, {"player_position", Point {i, j}.serialized()},
                            {"remaining_walls", currentPlayerNWalls}, {"username", currentPlayerUsername},
                            {"finish_line", static_cast<int>(currentFinishLine)}};
                        playerArray.push_back(playerJson);
                    } else {
                        // This only concerns placement between 4 player cells
                        WallOrientation wallOrientation = std::dynamic_pointer_cast<Corridor>(matrix.at(i).at(j))->getOrientation();
                        json wallJson = {{"wall_orientation", toJsonOutput(wallOrientation)}, {"wall_position", Point {i, j}.serialized()}};
                        wallArray.push_back(wallJson);
                    }
                }
            }
        }
    }
    json boardJson = {{"walls", wallArray}, {"players", playerArray}, {"n_of_players", NOfPlayers}};
    return boardJson;
}

void Board::deserialized(const std::string &serializedBoard)
{
    auto boardJson(json::parse(serializedBoard));
    json players = boardJson.at("players"), walls = boardJson.at("walls");

    for (auto &player : players) {
        // Build each player from serialized information
        PawnColors currentColor = static_cast<PawnColors>(player.at("player_id").get<int>());
        int currentPlayerNWalls = player.at("remaining_walls").get<int>();
        int x = player.at("player_position").at("x").get<int>(), y = player.at("player_position").at("y").get<int>();
        Point currentPosition {x, y};
        FinishLine currentFinishLine = static_cast<FinishLine>(player.at("finish_line").get<int>());
        std::string currentPlayerUsername = player.at("username").get<std::string>();
        std::shared_ptr<Player> newPlayer
            = std::make_shared<Player>(currentColor, currentPosition, currentPlayerNWalls, currentFinishLine, currentPlayerUsername);
        spawnPlayer(newPlayer);
    }

    for (auto &wall : walls) {
        // Build wall from serialized information
        WallOrientation currentOrientation
            = wall.at("wall_orientation").get<std::string>() == "wall_vertical" ? WallOrientation::Vertical : WallOrientation::Horizontal;
        int x = wall.at("wall_position").at("x").get<int>(), y = wall.at("wall_position").at("y").get<int>();

        auto corridor = std::make_shared<Corridor>(currentOrientation);
        corridor->placeWall();

        matrix.at(x).at(y) = corridor;
    };
}
