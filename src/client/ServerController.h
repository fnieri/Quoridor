/**
 * @file ServerController.h
 * @author Kourieh Anne-Marie
 * @brief ServerController that gets messages from the Server and sends them to the correct Model and also sends messages to the Server gotten from the ViewController
 * @date 2022-02-25
 *
*/

#pragma once

#include "Controller.h"

class ServerController : public Controller
{
    std::shared_ptr<Board> board;
    int nPlayers;
    std::vector<std::shared_ptr<Player>> players;
    int currentGameId;
    std::string gameSetup;

    void makeDictPlayer();
    std::map<PawnColors, std::shared_ptr<Player>> dictPlayer;

public:
    ServerController();
    ~ServerController() = default;

    virtual void setBoard(std::shared_ptr<Board> aBoard) override; 
    virtual void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers) override; 
    
    void setDict(std::map<PawnColors, std::shared_ptr<Player>> dict_play);

    /* To Game Model */
    void movePlayer(std::string action);
    void placeWall(std::string action);

    /* To Network Model (the server) */
    virtual void registerPlayer(std::string username, std::string password) override;
    virtual void logIn(std::string username, std::string password) override;
    virtual void logOut() override;

    virtual void startGame() override;
    virtual void saveGame(std::string username) override;
    virtual void pauseGame(std::string username) override;

    virtual void sendInvite(std::string aFriend, std::string gameSetup) override;
    virtual void joinGame(int gameId)  override;
    virtual void askToPause(std::string aFriend)  override;

    virtual void sendFriendRequest(std::string receiver)  override;
    virtual void checkLeaderBoard()  override;

    /* To Chat Model (there isn't yet a chat model) */

    virtual void sendDirectMessage(std::string sender, std::string receiver, std::string msg) override;
    virtual void sendGroupMessage(std::string sender, std::string msg, int gameId) override;
    
    virtual bool isDirectMessageReceived(bool received = false) override;
    virtual bool isGroupMessageReceived(bool received = false) override;

    nlohmann::json receiveGroupMessage(std::string msg);
    nlohmann::json receiveDirectMessage(std::string msg);

    virtual void loadDirectMessages(std::string username) override;
    virtual void loadGroupMessages(int gameId) override;
    
    /* Noticing the view */
    virtual bool isGameOver(bool over = false) override;
};