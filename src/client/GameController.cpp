//
// Created by louis on 26/02/2022.
//

#include "GameController.h"

using json = nlohmann::json;

GameController::GameController(int nPlayers, int currentPlayerIndex, int gameId)
    : nPlayers(nPlayers)
    , currentPlayerIndex(currentPlayerIndex)
    , gameId(gameId)
{
    std::vector<Point> startPositions {{4, 8}, {4, 0}, {0, 4}, {8, 4}};
    std::vector<FinishLine> finishLines {FinishLine::North, FinishLine::South, FinishLine::East, FinishLine::West};
    for (int i = 0; i < nPlayers; i++) {
        // TODO handle username
        auto p = std::make_shared<Player>(PawnColors(i), startPositions.at(i), 10, finishLines.at(i), "louis");

        players.push_back(p);

        board->spawnPlayer(p);
    }

    mainController.registerObserver(this);

    mainController.startHandling();
}

std::shared_ptr<Board> GameController::getBoard()
{
    return board;
}

bool GameController::isMoveValid(Point movePoint)
{
    PlayerAction move {board, players.at(currentPlayerIndex), movePoint/2};
    return move.isActionValid();
}

bool GameController::isWallValid(Point movePoint, int orientation)
{
    WallOrientation wallOrientation = orientation == 0 ? WallOrientation::Vertical : WallOrientation::Horizontal;
    if ((wallOrientation == WallOrientation::Horizontal && movePoint.y() % 2 == 0) || (wallOrientation == WallOrientation::Vertical && movePoint.x() % 2 == 0))
        return false;
    WallAction wallAction {board, players.at(currentPlayerIndex), movePoint/2, wallOrientation};
    return wallAction.isWallPlacementValid();
}

void GameController::movePlayer(Point movePoint)
{
    PlayerAction move {board, players.at(currentPlayerIndex), movePoint/2};
    move.executeAction();
    json to_send = SerializableMessageFactory::serializePawnAction(move, currentPlayerIndex);
    mainController.sendAsync(to_send.dump());
}

void GameController::placeWall(Point wallPoint, int orientation)
{
    WallOrientation wallOrientation = orientation == 0 ? WallOrientation::Vertical : WallOrientation::Horizontal;
    wallPoint/2;
    if (wallOrientation == WallOrientation::Horizontal) {
        wallPoint.y(wallPoint.y()+1);
    } else {
        wallPoint.x(wallPoint.x()+1);
    }
    WallAction wallAction {board, players.at(currentPlayerIndex), wallPoint, wallOrientation};
    wallAction.executeAction();
    json to_send = SerializableMessageFactory::serializeWallAction(wallAction, currentPlayerIndex);
    mainController.sendAsync(to_send.dump());
}

std::vector<std::vector<int>> GameController::getBoardAsIntMatrix()
{
    std::vector<std::vector<int>> boardIntMatrix;
    std::vector<std::vector<std::shared_ptr<BoardComponent>>> boardMatrix = board->getRotatedBoardMatrix(players.at(currentPlayerIndex)->getFinishLine());

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
    std::vector<std::vector<std::shared_ptr<BoardComponent>>> boardMatrix = board->getRotatedBoardMatrix(players.at(currentPlayerIndex)->getFinishLine());

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

void GameController::update(QuoridorEvent)
{
    auto lastRequest {mainController.getLastAsyncRequest()};
}
