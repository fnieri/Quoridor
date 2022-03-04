//
// Created by louis on 26/02/2022.
//
#pragma once

#include "Board.h"
#include "BoardComponent.h"
#include "Cell.h"
#include "Corridor.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerEnum.h"
#include "ServerBridge.h"
#include "ServerController.h"
#include "WallAction.h"
#include "WallEnum.h"
#include "src/common/Point.h"
#include "src/common/SerializableMessageFactory.h"
#include "MainController.h"
#include "src/common/Observer.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using json = nlohmann::json;

class GameController : public Observer
{
    // Server Receipt Variables
    json logInMessage;
    json registerMessage;
    json friendReqReceipt;
    json friendsListReceipt;
    json friendsRequestSentList;
    json friendsRequestReceivedList;
    json groupMessage;
    json directMessage;

    std::shared_ptr<ServerController> serverController = std::make_shared<ServerController>();
    std::shared_ptr<Board> board = std::make_shared<Board>();
    int nPlayers;
    std::vector<std::shared_ptr<Player>> players;
    int currentPlayerIndex = 0; // index of the current player in the vector of Players
    int gameId;
    std::string gameSetup;
    const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
              occupiedHorizontalQuoridor = 7;
    MainController mainController {"localhost", 12345};

public:
    GameController(int nPlayers, int currentPlayerIndex, int gameId);

    /**
     * @brief Updating the Int Matrix accordingly to the Board Model
     * (Louis' method)
     * @param boardIntMatrix
     */
    void updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix);

    /* Setters */
    void setBoard(std::shared_ptr<Board> aBoard);
    void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers);

    /**
     * @brief Set the Game Setup object and send it to the server
     *
     * @param gameS the setup given
     */
    void setGameSetup(std::string gameS);

    /* Getters */

    /**
     * @brief Get the Board object
     * (Louis' method)
     * @return std::shared_ptr<Board> the board
     */
    std::shared_ptr<Board> getBoard();

    /**
     * @brief Get the Board As Int Matrix object
     * (Louis' method)
     * @return std::vector<std::vector<int>> the matrix
     */
    std::vector<std::vector<int>> getBoardAsIntMatrix();

    void startGame();

    /* ---- Sending messages to Server/Model ---- */
    /**
     * @brief Plays a PlayerAction, when the current player moves his pawn
     * (Louis' changes)
     * @param x in the corresponding matrix
     * @param y
     */
    void movePlayer(int x, int y);

    /**
     * @brief Plays a WallAction, when the current player places one of his walls on the board
     * (Louis' changes)
     * @param x in the corresponding matrix
     * @param y
     * @param orientation either a horizontal or a vertical wall
     */
    void placeWall(int x, int y, int orientation);

    bool registerPlayer(std::string username, std::string password);
    bool logIn(std::string username, std::string password);

    void saveGame(std::string username);

    //  void joinGame(int gameId)  ;

    void sendFriendRequest(std::string sender, std::string receiver);
    //    void checkLeaderBoard();

    void sendDirectMessage(std::string sender, std::string receiver, std::string msg);
    void sendGroupMessage(std::string sender, std::string msg, int gameId, std::vector<std::string> receivers);

    void loadDirectMessages(std::string sender, std::string receiver);

    /* Booleans */
    bool isGameOver(bool over = false);

    /**
     * @brief Checks wether a playerAction was valid or not
     * (Louis'method)
     * @param x the X position in the matrix of move
     * @param y the Y position in the matrix of move
     * @return true
     * @return false
     */
    bool isMoveValid(int x, int y);

    /**
     * @brief Checks wether a wallAction was valid or not
     * (Louis'method)
     * @param x the X position in the matrix of the wall
     * @param y the Y position in the matrix of the wall
     * @param orientation horizontal or vertical
     * @return true
     * @return false
     */
    bool isWallValid(int x, int y, int orientation);

    /* Server Receipt : We handle in ViewController the Message from the Server
    Or do we just send with multiple methods
    */
    void logInReceipt(std::string msg);
    void registerReceipt(std::string msg);
    void friendRequestReceipt(std::string msg);
    void sendFriendsList(std::string msg);
    void sendfriendsRequestSentList(std::string msg);
    void sendfriendsRequestReceivedList(std::string msg);
    void receiveGroupMessage(std::string msg);
    void receiveDirectMessage(std::string msg);

    // Getters
    nlohmann::json getLogInReceipts();
    nlohmann::json getRegisterReceipts();
    nlohmann::json getFriendsListReceipt();
    nlohmann::json getFriendsRequestReceipts();
    nlohmann::json getFriendsRequestSentList();
    nlohmann::json getFriendsRequestReceivedList();
    nlohmann::json getDirectMessage();
    nlohmann::json getGroupMessage();

    // Booleans
    bool isDirectMessageReceived(bool received = false);
    bool isGroupMessageReceived(bool received = false);
    bool isLogInReceived(bool received = false);
    bool isRegisterReceived(bool received = false);

    bool isFriendsRequestReceived(bool received = false);
    bool isFriendsRequestSentListReceived(bool received = false);
    bool isFriendsRequestReceivedListReceived(bool received = false);
    bool isFriendsListReceived(bool received = false);

    /**
     * Process request
     * @param request request to be processed, should be json formatted
     */
    void processRequest(std::string message);

    void update(QuoridorEvent) override{
        
    }
};
