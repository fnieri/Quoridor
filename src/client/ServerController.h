/**
 * @file ServerController.h
 * @author Kourieh Anne-Marie
 * @brief ServerController that gets messages from the Server and sends them to the correct Model and also sends messages to the Server gotten from the ViewController
 * @date 2022-02-25
 * (every overriden methods are not documented here, but in the Controller class)
 *
*/

#pragma once

#include "Controller.h"

class ServerController : public Controller
{
    std::shared_ptr<Board> board;                       // The Game Model
    int nPlayers;                                       // The Number of Players
    std::vector<std::shared_ptr<Player>> players;       // A vector containing pointers to all the Players 
    std::map<PawnColors, std::shared_ptr<Player>> dictPlayer;   // A map with Colors of a player's pawn and the corresponding Player

public:
    ServerController();
    ~ServerController() = default;
    
    /* Setters */
    
    virtual void setBoard(std::shared_ptr<Board> aBoard) override; 
    
    virtual void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers) override; 
    
    /**
     * @brief Set the Dict object which is the name given to the map
     * 
     * @param dict_play the map given
     */
    void setDict(std::map<PawnColors, std::shared_ptr<Player>> dict_play);

    /* ---- To Game Model ---- */
    
    /**
     * @brief The servers sends an action (a pawn move) which was played by another player to the model and the view will update itself
     * 
     * @param action formatted in json
     */
    void movePlayer(std::string action);
    
    /**
     * @brief The servers sends an action (a wall placement) which was played by another player to the model and the view will update itself
     * 
     * @param action also formatted in json
     */
    void placeWall(std::string action);

    /* ---- To Network Model ---- */
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

    /* ---- To Chat Model ---- */

    virtual void sendDirectMessage(std::string sender, std::string receiver, std::string msg) override;
    virtual void sendGroupMessage(std::string sender, std::string msg, int gameId) override;
    
    virtual bool isDirectMessageReceived(bool received = false) override;
    virtual bool isGroupMessageReceived(bool received = false) override;

    /**
     * @brief When the server has got a message sent from another player, it is sent back to the View to show it to everyone in the Multiplayer Game
     * 
     * @param msg the message sent (formatted in json)
     * @return nlohmann::json : the message is sent in json to the View
     */
    nlohmann::json receiveGroupMessage(std::string msg);
    
    /**
     * @brief When the server has got a message sent from another player, it is sent back to the View to show it to the other person in the Direct Message Chatbox
     * 
     * @param msg the message sent (formatted in json)
     * @return nlohmann::json : the message is sent in json to the View
     */
    nlohmann::json receiveDirectMessage(std::string msg);

    virtual void loadDirectMessages(std::string username) override;
    virtual void loadGroupMessages(int gameId) override;
    
    /* Notify the view */
    virtual bool isGameOver(bool over = false) override;
};