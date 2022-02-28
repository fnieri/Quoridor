/**
 * @file ViewController.h
 * @author Kourieh Anne-Marie
 * @brief ViewController that gets messages from the View and sends them to the correct Model
 * @date 2022-02-25
 * 
*/

#pragma once

#include "Controller.h"

class ServerController;

class ViewController : public Controller
{
private:
    std::shared_ptr<Board> board;
    int nPlayers;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<ServerController> serverController;
    int currentPlayerIndex = 0; // index of the current player in the vector of Players
    int currentGameId;
    std::string gameSetup;
public:
    ViewController(std::shared_ptr<ServerController> serverController, int nPlayers);
    ~ViewController() = default;

    /* Setters */

    virtual void setBoard(std::shared_ptr<Board> aBoard) override; 
    virtual void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers) override; 
    
    /* To Game Model */
    /**
     * @brief Plays a PlayerAction, when the current player moves his pawn
     *
     * @param p the position to move the pawn to
     */
    void movePlayer(Point p);

    /**
     * @brief Plays a WallAction, when the current player places one of his walls on the board
     *
     * @param p the corridor in which the wall will be placed
     * @param orientation
     */
    void placeWall(Point p, WallOrientation orientation);

    /* To Network Model (all of these are to send to the ServerController) */ 
    virtual void registerPlayer(std::string username, std::string password) override;
    virtual void logIn(std::string username, std::string password) override;
    virtual void logOut() override;

    void setGameSetup(std::string gameS);

    virtual void startGame() override;
    virtual void saveGame(std::string username) override;
    virtual void pauseGame(std::string username) override;

    virtual void sendInvite(std::string aFriend, std::string gameSetup) override;
    virtual void joinGame(int gameId)  override;
    virtual void askToPause(std::string aFriend)  override;

    virtual void sendFriendRequest(std::string receiver)  override;
    virtual void checkLeaderBoard()  override;

    /* To Chat Model (all of these are to send to the ServerController as well) */
    virtual void sendDirectMessage(std::string sender, std::string receiver, std::string msg) override;
    virtual void sendGroupMessage(std::string sender, std::string msg, int gameId) override;
    
    virtual bool isDirectMessageReceived(bool received = false) override;
    virtual bool isGroupMessageReceived(bool received = false) override;

    nlohmann::json receiveGroupMessage(nlohmann::json msg);
    nlohmann::json receiveDirectMessage(nlohmann::json msg);
    
    virtual void loadDirectMessages(std::string username) override;
    virtual void loadGroupMessages(int gameId) override;
    
    /* Noticing the view */
    virtual bool isGameOver(bool over = false) override;
};