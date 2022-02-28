//
// Created by louis on 26/02/2022.
//

#include "GameController.h"

GameController::GameController(int nPlayers, int currentPlayerIndex, int gameId)
    : nPlayers(nPlayers)
    , currentPlayerIndex(currentPlayerIndex)
    , gameId(gameId)
{
    std::vector<Point> startPositions {{4, 8}, {4, 0}, {0, 4}, {8, 4}};
    for (int i = 0; i < nPlayers; i++) {
        auto p = std::make_shared<Player>(PawnColors(i), startPositions.at(i), 10, FinishLine::North);

        players.push_back(p);

        board->spawnPlayer(p);

        // Temporary way of adding the players to the board
        //        PlayerAction spawnPlayer {board, p, startPositions.at(i)};
        //        spawnPlayer.executeAction();
    }
}

std::shared_ptr<Board> GameController::getBoard()
{
    return board;
}

bool GameController::isMoveValid(int x, int y)
{
    PlayerAction move {board, players.at(currentPlayerIndex), Point(x / 2, y / 2)};
    return move.isActionValid();
}

bool GameController::isWallValid(int x, int y, int orientation)
{
    WallOrientation wallOrientation = orientation == 0 ? WallOrientation::Vertical : WallOrientation::Horizontal;
    if ((wallOrientation == WallOrientation::Horizontal && y % 2 == 0) || (wallOrientation == WallOrientation::Vertical && x % 2 == 0))
        return false;
    WallAction wallAction {board, players.at(currentPlayerIndex), Point(x / 2, y / 2), wallOrientation};
    return wallAction.isWallPlacementValid();
}

void GameController::movePlayer(int x, int y)
{
    PlayerAction move {board, players.at(currentPlayerIndex), Point(x / 2, y / 2)};
    move.executeAction();
}

void GameController::placeWall(int x, int y, int orientation)
{
    WallOrientation wallOrientation = orientation == 0 ? WallOrientation::Vertical : WallOrientation::Horizontal;
    int wallX;
    int wallY;
    if (wallOrientation == WallOrientation::Horizontal) {
        wallX = x / 2;
        wallY = y / 2 + 1;
    } else {
        wallX = x / 2 + 1;
        wallY = y / 2;
    }
    WallAction wallAction {board, players.at(currentPlayerIndex), Point(x / 2, y / 2), wallOrientation};
    wallAction.executeAction();
}

std::vector<std::vector<int>> GameController::getBoardAsIntMatrix()
{
    std::vector<std::vector<int>> boardIntMatrix;
    std::vector<std::vector<std::shared_ptr<BoardComponent>>> boardMatrix = board->getBoardMatrix();

    for (int y = 0; y < board->getCellSize(); y++) {
        boardIntMatrix.push_back(std::vector<int>());
        for (int x = 0; x < board->getCellSize(); x++) {
            if (board->isCell({x, y})) {
                if (board->isFree({x, y}))
                    boardIntMatrix[y].push_back(freeCell);
                else
                    boardIntMatrix[y].push_back(playerOne);
            } else if (boardMatrix.at(x).at(y) && boardMatrix.at(x).at(y)->isOccupied()) {
                auto orientation = std::dynamic_pointer_cast<Corridor>(boardMatrix.at(x).at(y))->getOrientation();
                boardIntMatrix[y].push_back((orientation == WallOrientation::Vertical ? occupiedVerticalQuoridor : occupiedHorizontalQuoridor));
            } else
                boardIntMatrix[y].push_back(emptyQuoridor);
        }
    }
    return boardIntMatrix;
};

void GameController::updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix)
{
    boardIntMatrix.clear();
    std::vector<std::vector<std::shared_ptr<BoardComponent>>> &boardMatrix = board->getBoardMatrix();

    for (int y = 0; y < boardMatrix.size(); y++) {
        std::vector<int> row;
        for (int x = 0; x < boardMatrix[y].size(); x++) {
            if (board->isCell({x, y})) {
                if (board->isFree({x, y}))
                    row.push_back(freeCell);
                else {
                    auto playerCell = (std::dynamic_pointer_cast<Cell>(boardMatrix.at(x).at(y)));
                    switch (playerCell->getPlayer()->getColor()) {
                    case PawnColors::Yellow:
                        row.push_back(playerOne);
                        break;
                    case PawnColors::Green:
                        row.push_back(playerTwo);
                        break;
                    case PawnColors::Blue:
                        row.push_back(playerThree);
                        break;
                    case PawnColors::Purple:
                        row.push_back(playerFour);
                        break;
                    }
                }
            } else if (boardMatrix.at(x).at(y) && boardMatrix.at(x).at(y)->isOccupied()) {
                auto orientation = std::dynamic_pointer_cast<Corridor>(boardMatrix.at(x).at(y))->getOrientation();
                row.push_back((orientation == WallOrientation::Vertical ? occupiedVerticalQuoridor : occupiedHorizontalQuoridor));
            } else
                row.push_back(emptyQuoridor);
        }
        boardIntMatrix.push_back(row);
    }
};
