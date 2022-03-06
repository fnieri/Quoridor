#include "ViewController.h"
#include "../common/Point.h"
#include "Board.h"
#include "BoardComponent.h"
#include "Cell.h"
#include "Controller.h"
#include "Corridor.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerEnum.h"
#include "serverBridge.h"
#include "WallAction.h"
#include "WallEnum.h"

#include <memory>
#include <vector>

using json = nlohmann::json;

ViewController::ViewController(std::shared_ptr<serverBridge> serverBridge, int nPlayers)
    : serverBridge {serverBridge}
    , nPlayers {nPlayers}
{
    // Player spawn moved to startGame()
}

ViewController::ViewController(int nPlayers, int currentPlayerIndex, int gameId)
    : nPlayers(nPlayers)
    , currentPlayerIndex(currentPlayerIndex)
    , gameId(gameId)
{
}

void ViewController::setBoard(std::shared_ptr<Board> theBoard)
{
    board = theBoard;
}

void ViewController::setPlayers(std::vector<std::shared_ptr<Player>> thePlayers)
{
    players = thePlayers;
}

void ViewController::setGameSetup(std::string gameS)
{
    gameSetup = gameS;
}

std::shared_ptr<Board> ViewController::getBoard()
{
    return board;
}

void ViewController::updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix)
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

std::vector<std::vector<int>> ViewController::getBoardAsIntMatrix()
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

/* To Game Model */

void ViewController::movePlayer(int x, int y)
{
    // Old method :
    /* std::shared_ptr<PlayerAction> action = std::make_shared<PlayerAction>(board, players[currentPlayerIndex], p / 2);
    // if (action->executeAction() && !action->isGameOver())
    //    currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers; // change turns if the PlayerAction is valid
    // else if (action->isGameOver())
    //     isGameOver(true);
    */

    // Rotate the point
    Point rotP = board->getRotatedMatrixPosition(Point {x, y}, players.at(currentPlayerIndex)->getFinishLine(), true);

    // Louis' method :
    PlayerAction move {board, players.at(currentPlayerIndex), Point(rotP.x() / 2, rotP.y() / 2)};
    move.executeAction();
}

void ViewController::placeWall(int x, int y, int orientation)
{
    // Old method :
    /* std::shared_ptr<WallAction> action = std::make_shared<WallAction>(board, players[currentPlayerIndex], p / 2, orientation);
    if (action->executeAction())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers;
     */

    // Rotate the point, orientation and change position accordingly
    FinishLine f = players.at(currentPlayerIndex)->getFinishLine();
    Point rotP = board->getRotatedMatrixPosition(Point {x, y}, f, true);
    int wallX = rotP.x() / 2;
    int wallY = rotP.y() / 2;

    switch (f) {
    case FinishLine::South:
        wallX++;
        wallY++;
        break;
    case FinishLine::East:
        wallY++;
        orientation = (++orientation) % 2;
        break;
    case FinishLine::West:
        wallX++;
        orientation = (++orientation) % 2;
        break;
    case FinishLine::North:
    default:
        break;
    }

    WallOrientation wallOrientation = orientation == 0 ? WallOrientation::Vertical : WallOrientation::Horizontal;

    WallAction wallAction {board, players.at(currentPlayerIndex), Point(wallX, wallY), wallOrientation};
    wallAction.executeAction();
}

void ViewController::startGame()
{
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::vector<std::shared_ptr<Player>> players;
    std::map<PawnColors, std::shared_ptr<Player>> dictPlayer;

    // Initialize and spawn the players
    std::vector<Point> startPositions {{4, 8}, {4, 0}, {0, 4}, {8, 4}};
    std::vector<FinishLine> finishLines {FinishLine::North, FinishLine::South, FinishLine::East, FinishLine::West};

    for (int i = 0; i < nPlayers; i++) {
        // FIXME NEEDS USERNAME!!
        auto p = std::make_shared<Player>(PawnColors(i), startPositions.at(i), 10, finishLines.at(i), "asd");

        players.push_back(p);

        board->spawnPlayer(p);
    }

    setBoard(board);
    setPlayers(players);
    serverBridge->setBoard(board);
    serverBridge->setPlayers(players);
    serverBridge->setDict(dictPlayer);
}

void ViewController::saveGame(std::string username)
{
    serverBridge->saveGame(username);
}

void ViewController::pauseGame(std::string username)
{
    serverBridge->pauseGame(username);
}

void ViewController::registerPlayer(std::string username, std::string password)
{
    serverBridge->registerPlayer(username, password);
}

void ViewController::logIn(std::string username, std::string password)
{
    serverBridge->logIn(username, password);
}

void ViewController::logOut()
{
    serverBridge->logOut();
}

void ViewController::sendInvite(std::string aFriend, std::string gameSetup)
{
    serverBridge->sendInvite(aFriend, gameSetup);
}

void ViewController::joinGame(int gameId)
{
    serverBridge->joinGame(gameId);
}

void ViewController::askToPause(std::string aFriend)
{
    serverBridge->askToPause(aFriend);
}

void ViewController::sendFriendRequest(std::string receiver)
{
    serverBridge->sendFriendRequest(receiver);
}

void ViewController::checkLeaderBoard()
{
    serverBridge->checkLeaderBoard(); // or call immediatly ELO and give to the view ?
}

void ViewController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    serverBridge->sendDirectMessage(sender, receiver, msg);
}

void ViewController::sendGroupMessage(std::string sender, std::string msg, int gameId)
{
    serverBridge->sendGroupMessage(sender, msg, gameId);
}

bool ViewController::isGroupMessageReceived(bool received)
{
    if (serverBridge->isGroupMessageReceived())
        return true;
    else
        return received;
}

bool ViewController::isDirectMessageReceived(bool received)
{
    if (serverBridge->isDirectMessageReceived())
        return true;
    else
        return received;
}

json ViewController::receiveGroupMessage(json msg)
{
    isGroupMessageReceived(true);
    return msg;
}

json ViewController::receiveDirectMessage(json msg)
{
    isDirectMessageReceived(true);
    return msg;
}

void ViewController::loadDirectMessages(std::string username)
{
    serverBridge->loadDirectMessages(username);
}

void ViewController::loadGroupMessages(int gameId)
{
    serverBridge->loadGroupMessages(gameId);
}

bool ViewController::isGameOver(bool over)
{
    serverBridge->isGameOver(over);
    return over;
}

bool ViewController::isMoveValid(int x, int y)
{
    PlayerAction move {board, players.at(currentPlayerIndex), Point(x / 2, y / 2)};
    return move.isActionValid();
}

bool ViewController::isWallValid(int x, int y, int orientation)
{
    WallOrientation wallOrientation = orientation == 0 ? WallOrientation::Vertical : WallOrientation::Horizontal;
    if ((wallOrientation == WallOrientation::Horizontal && y % 2 == 0) || (wallOrientation == WallOrientation::Vertical && x % 2 == 0))
        return false;
    WallAction wallAction {board, players.at(currentPlayerIndex), Point(x / 2, y / 2), wallOrientation};
    return wallAction.isWallPlacementValid();
}