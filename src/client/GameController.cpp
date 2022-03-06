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
    for (int i = 0; i < nPlayers; i++) {
        auto p = std::make_shared<Player>(PawnColors(i), startPositions.at(i), 10, FinishLine::North);

        players.push_back(p);

        board->spawnPlayer(p);

        // Temporary way of adding the players to the board
        //        PlayerAction spawnPlayer {board, p, startPositions.at(i)};
        //        spawnPlayer.executeAction();
    }

    mainController.registerObserver(this);

    mainController.startHandling();
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
    json to_send = SerializableMessageFactory::serializePawnAction(move, currentPlayerIndex);
    mainController.getSyncAnswer(to_send.dump());
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
    json to_send = SerializableMessageFactory::serializeWallAction(wallAction, currentPlayerIndex);
    mainController.sendAsync(to_send.dump());
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

bool GameController::registerPlayer(std::string username, std::string password)
{
    json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTRATION, username, password);
    json answer = json::parse(mainController.getSyncAnswer(to_send.dump()));
    return answer["action"] == toJsonString(ClientAuthAction::REGISTRATION) && answer["status"] == toJsonString(RequestStatus::SUCCESS);
};

bool GameController::logIn(std::string username, std::string password)
{
    json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, username, password);
    json answer = json::parse(mainController.getSyncAnswer(to_send.dump()));
    return answer["action"] == toJsonString(ClientAuthAction::LOGIN) && answer["status"] == toJsonString(RequestStatus::SUCCESS);
};

void GameController::saveGame(std::string username)
{
    json to_send = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::PROPOSE_SAVE, username);
    mainController.getSyncAnswer(to_send.dump());
};

void GameController::sendFriendRequest(std::string sender, std::string receiver)
{
    json to_send = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, sender, receiver);
    mainController.sendAsync(to_send.dump());
};

void GameController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    json to_send = SerializableMessageFactory::serializeFriendMessage(sender, receiver, msg); // make a json formated message
    mainController.sendAsync(to_send.dump());
}

void GameController::sendGroupMessage(std::string sender, std::string msg, int gId, std::vector<std::string> receivers)
{
    json to_send = SerializableMessageFactory::serializeInGameMessage(sender, receivers, msg, gId);
    mainController.sendAsync(to_send.dump());
}

void GameController::update(QuoridorEvent)
{
    auto lastRequest {mainController.getLastAsyncRequest()};
}

json GameController::getLeaderboard()
{
    json leaderboardReq = SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD);
    return leaderboardReq;
}

json GameController::getFriendList()
{
    json friendListReq = SerializableMessageFactory::serializeRequestExchange(DataType::FRIENDS_LIST);
    return friendListReq;
}

void GameController::acceptFriendRequest(const std::string &friendRequestSender, const std::string &friendRequestReceiver)
{
    json requestJson = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, friendRequestSender, friendRequestReceiver);
    mainController.sendAsync(requestJson.dump());
}

void GameController::removeFriendRequest(const std::string &friendRemoveSender, const std::string &friendRemoveReceiver)
{
    json removeJson = SerializableMessageFactory::serializeFriendRemove(friendRemoveSender, friendRemoveReceiver);
    mainController.sendAsync(removeJson.dump());
}

void GameController::getFriendsChats()
{
    json chatJson = SerializableMessageFactory::serializeRequestExchange(DataType::CHATS);
    mainController.sendAsync(chatJson.dump());
}

void GameController::createGame(std::vector<std::string> &players)
{
    json gameJson = SerializableMessageFactory::serializeGameSetup(GameMode::CLASSIC, players);
    mainController.sendAsync(gameJson.dump());
}

json GameController::loadExistingGames()
{
    json gamesJson = SerializableMessageFactory::serializeRequestExchange(DataType::GAME_IDS);
    return gamesJson;
}

// void GameController::processRequest(std::string serRequest)
// {
//     json request(json::parse(serRequest));

//     if (request["domain"] == toJsonString(Domain::AUTH)) {
//         processAuth(serRequest);

//     } else if (request["domain"] == toJsonString(Domain::RELATIONS)) {
//         processRelations(serRequest);

//     } else if (request["domain"] == toJsonString(Domain::CHAT)) {
//         processChatbox(serRequest);

//     } else if (request["domain"] == toJsonString(Domain::RESOURCE_REQUEST)) {
//         processResourceRequest(serRequest);

//     } else if (request["domain"] == toJsonString(Domain::IN_GAME_RELATED)) {
//         processGameAction(serRequest);

//     } else if (request["domain"] == toJsonString(Domain::GAME_SETUP)) {
//         processGameSetup(serRequest);
//     }
// }

// void GameController::processAuth(std::string message)
// {
// }

// void GameController::processRelations(std::string message)
// {
// }

// void GameController::processResourceRequest(std::string message)
// {
// }
// void GameController::processChatbox(std::string message)
// {
// }

// void GameController::processGameSetup(std::string message)
// {
// }

// void GameController::processGameAction(std::string message)
// {
// }
