#include "ViewController.h"
#include "Controller.h"
#include "Corridor.h"
#include "Cell.h"
#include "Board.h"
#include "BoardComponent.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerEnum.h"
#include "../common/Point.h"
#include "ServerController.h"
#include "WallAction.h"
#include "WallEnum.h"

#include <memory>
#include <vector>

using json = nlohmann::json;


ViewController::ViewController(int nPlayers, int currentPlayerIndex, int gameId)
    : nPlayers(nPlayers)
    , currentPlayerIndex(currentPlayerIndex)
    , gameId(gameId)
{
    std::vector<Point> startPositions {{4, 8}, {4, 0}, {0, 4}, {8, 4}};
    for (int i = 0; i < nPlayers; i++) {
        auto p = std::make_shared<Player>(PawnColors(i), startPositions.at(i), 10, FinishLine::North);

        players.push_back(p);

        board->spawnPlayer(p);
    }

    serverController->setViewController(shared_from_this());
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
    serverController->sendGameSetup(gameS);
}

std::shared_ptr<Board> ViewController::getBoard()
{
    return board;
}

void ViewController::updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix)
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

std::vector<std::vector<int>> ViewController::getBoardAsIntMatrix()
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

void ViewController::startGame()
{
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::vector<std::shared_ptr<Player>> players;
    std::map<PawnColors, std::shared_ptr<Player>> dictPlayer;

    // loop for made by Léo
    for (int i = 0; i < nPlayers; i++) 
    {
        // TODO: Change spawn position of players
        Point pos{i, i};
        auto p = std::make_shared<Player>(PawnColors(i), pos, 10, FinishLine(i));
        p->setIndex(i);
        players.push_back(p);

        board->spawnPlayer(p);

        // dictPlayer.insert(players[i]->getColor(), players[i]);
    }

    setBoard(board);
    setPlayers(players);
    serverController->setBoard(board);
    serverController->setPlayers(players);
    serverController->setDict(dictPlayer);
}

/*  Sending these to Model/Server  */
void ViewController::movePlayer(int x, int y)
{
    // Old method :
    /* std::shared_ptr<PlayerAction> action = std::make_shared<PlayerAction>(board, players[currentPlayerIndex], p / 2);
    // if (action->executeAction() && !action->isGameOver())
    //    currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers; // change turns if the PlayerAction is valid
    // else if (action->isGameOver())
    //     isGameOver(true);
    */

    // Louis' method :
    PlayerAction move {board, players.at(currentPlayerIndex), Point(x / 2, y / 2)};
    if (move.executeAction()) serverController->sendPlayerAction(move, currentPlayerIndex);
}

void ViewController::placeWall(int x, int y, int orientation)
{
    // Old method :
    /* std::shared_ptr<WallAction> action = std::make_shared<WallAction>(board, players[currentPlayerIndex], p / 2, orientation);
    if (action->executeAction())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers;
     */

    // Louis' method :
    
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
    if (wallAction.executeAction()) serverController->sendWallAction(wallAction, currentPlayerIndex);
}

void ViewController::saveGame(std::string username)
{
    serverController->sendSaveGameRequest(username);
}

void ViewController::pauseGame(std::string username)
{
    serverController->sendPauseRequest(username);
}

void ViewController::registerPlayer(std::string username, std::string password)
{
    serverController->sendRegisterRequest(username, password);
}

void ViewController::logIn(std::string username, std::string password)
{
    serverController->sendLogInRequest(username, password);
}

void ViewController::sendInvite(std::string aFriend)
{
    serverController->sendInvite(aFriend);
}
/*
void ViewController::joinGame(int gameId)
{
    serverController->joinGame(gameId);
}*/

void ViewController::sendFriendRequest(std::string sender, std::string receiver)
{
    serverController->sendFriendRequest(sender, receiver);
}

void ViewController::checkLeaderBoard()
{
    serverController->sendLeaderboardRequest();       
}

void ViewController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    serverController->sendDirectMessage(sender, receiver, msg);       
}

void ViewController::sendGroupMessage(std::string sender, std::string msg, int gameId)
{
    serverController->sendGroupMessage(sender, msg, gameId);       
}


void ViewController::loadDirectMessages(std::string sender, std::string receiver)
{
    serverController->sendDMChatBoxRequest(sender, receiver);       
}

// Booleans

bool ViewController::isGameOver(bool over)
{
    serverController->isGameOver(over);
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

// Work of 03/03

void ViewController::receiveGroupMessage(std::string msg)
{
    groupMessage = json::parse(msg);
    isGroupMessageReceived(true);
}

void ViewController::receiveDirectMessage(std::string msg)
{
    directMessage = json::parse(msg);
    isDirectMessageReceived(true);
}

void ViewController::logInReceipt(std::string msg)
{
    logInMessage = json::parse(msg);
    isLogInReceived(true);
}

void ViewController::registerReceipt(std::string msg)
{
    registerMessage = json::parse(msg);
    isRegisterReceived(true);
}

void ViewController::friendRequestReceipt(std::string msg)
{
    friendReqReceipt = json::parse(msg);
    isFriendsRequestReceived(true);
}

void ViewController::sendFriendsList(std::string msg)
{
    friendsListReceipt = json::parse(msg);
    isFriendsListReceived(true);
}

void ViewController::sendfriendsRequestSentList(std::string msg)
{
    friendsRequestSentList = json::parse(msg);
    isFriendsRequestSentListReceived(true);
}

void ViewController::sendfriendsRequestReceivedList(std::string msg)
{
    friendsRequestReceivedList = json::parse(msg);
    isFriendsRequestReceivedListReceived(true);
}

// Getters

json ViewController::getLogInReceipts()
{
    return logInMessage;
}

json ViewController::getRegisterReceipts()
{
    return registerMessage;
}

json ViewController::getFriendsRequestReceipts()
{
    return friendReqReceipt;
}

json ViewController::getFriendsRequestSentList()
{
    return friendsRequestSentList;
}

json ViewController::getFriendsRequestReceivedList()
{
    return friendsRequestReceivedList;
}

json ViewController::getDirectMessage()
{
    return directMessage;
}

json ViewController::getGroupMessage()
{
    return groupMessage;
}

// Booleans : the view calls these consistently to check wether the server has sent sth

bool ViewController::isGroupMessageReceived(bool received)
{
    return received;
}

bool ViewController::isDirectMessageReceived(bool received)
{
    return received;
}

bool ViewController::isLogInReceived(bool received)
{
    return received;
}

bool ViewController::isRegisterReceived(bool received)
{
    return received;
}

bool ViewController::isFriendsRequestReceived(bool received)
{
    return received;
}

bool ViewController::isFriendsRequestSentListReceived(bool received)
{
    return received;
}

bool ViewController::isFriendsRequestReceivedListReceived(bool received)
{
    return received;
}

bool ViewController::isFriendsListReceived(bool received)
{
    return received;
}
