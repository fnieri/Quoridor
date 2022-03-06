/**
 * @file ViewController.h
 * @author Kourieh Anne-Marie and Vanstappen Louis
 * @brief ViewController that gets messages from the View and sends them to the correct Model
 * @date 2022-02-25
 * (every overriden methods are not documented here, but in the Controller class)
 *
 */

#pragma once

#include "Controller.h"

class ServerController;

class ViewController : public Controller
{
private:
    std::shared_ptr<Board> board = std::make_shared<Board>(); // The Game Model
    int nPlayers; // The Number of Players
    std::vector<std::shared_ptr<Player>> players; // A vector containing pointers to all the Players
    std::shared_ptr<ServerController> serverController; // The Server Controller because we need to send messages from the View to the Server
    int currentPlayerIndex = 0; // Index of the current player in the vector of Players
    std::string gameSetup; // Json formatted message indicated the setup of the current game
    int gameId;
    const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
              occupiedHorizontalQuoridor = 7;

public:
    ViewController(std::shared_ptr<ServerController> serverController, int nPlayers);
    ViewController(int nPlayers, int currentPlayerIndex, int gameId); // Louis' Constructor
    ~ViewController() = default;

    /**
     * @brief Updating the Int Matrix accordingly to the Board Model
     * (Louis' method)
     * @param boardIntMatrix
     */
    void updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix);

    /* Setters */
    virtual void setBoard(std::shared_ptr<Board> aBoard) override;
    virtual void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers) override;

    /**
     * @brief Set the Game Setup object
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

    /* ---- To Game Model ---- */
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

    /* ---- To Network Model ---- */
    virtual void registerPlayer(std::string username, std::string password) override;
    virtual void logIn(std::string username, std::string password) override;
    virtual void logOut() override;

    virtual void startGame() override;
    virtual void saveGame(std::string username) override;
    virtual void pauseGame(std::string username) override;

    virtual void sendInvite(std::string aFriend, std::string gameSetup) override;
    virtual void joinGame(int gameId) override;
    virtual void askToPause(std::string aFriend) override;

    virtual void sendFriendRequest(std::string receiver) override;
    virtual void checkLeaderBoard() override;

    /* ---- To Chat Model ---- */
    virtual void sendDirectMessage(std::string sender, std::string receiver, std::string msg) override;
    virtual void sendGroupMessage(std::string sender, std::string msg, int gameId) override;

    /**
     * @brief When the server has got a message sent from another player, it is sent back to the View to show it to everyone in the Multiplayer Game
     * The view will call first the notifying methods to check if a message has been received or not
     *
     * @param msg the message in json
     * @return
     */
    nlohmann::json receiveGroupMessage(nlohmann::json msg);

    /**
     * @brief When the server has got a message sent from another player, it is sent back to the View to show it to everyone in the Multiplayer Game
     *
     * @param msg the message sent (formatted in json)
     * @return nlohmann::json : the message is sent in json to the View
     */
    nlohmann::json receiveDirectMessage(nlohmann::json msg);

    virtual void loadDirectMessages(std::string username) override;
    virtual void loadGroupMessages(int gameId) override;

    /* Notifying the view */
    virtual bool isDirectMessageReceived(bool received = false) override;
    virtual bool isGroupMessageReceived(bool received = false) override;
    virtual bool isGameOver(bool over = false) override;

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
};