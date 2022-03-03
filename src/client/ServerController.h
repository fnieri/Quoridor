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
    std::shared_ptr<Board> board = std::make_shared<Board>();;                       // The Game Model
    int nPlayers;                                       // The Number of Players
    std::vector<std::shared_ptr<Player>> players;       // A vector containing pointers to all the Players 
    std::map<PawnColors, std::shared_ptr<Player>> dictPlayer;   // A map with Colors of a player's pawn and the corresponding Player
    std::shared_ptr<ViewController> viewController = std::make_shared<ViewController>();;
    ServerBridge serverBridge {"localhost", 12345, this};  

public:
    ServerController();
    ~ServerController() = default;
    
    // make general send request function
    void sendServerRequest();
    void processRequest(std::string message);

    /* Setters */
    
    virtual void setBoard(std::shared_ptr<Board> aBoard) override; 
    
    virtual void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers) override; 
    
    /**
     * @brief Set the Dict object which is the name given to the map
     * 
     * @param dict_play the map given
     */
    void setDict(std::map<PawnColors, std::shared_ptr<Player>> dict_play);

    void setViewController(std::shared_ptr<ViewController> vController);

    /* ---- Sending Request TO The Server ---- */
    
    void sendPlayerAction(PlayerAction action, int playerId);
    void sendWallAction(WallAction action, int playerId);

    virtual void sendRegisterRequest(std::string username, std::string password) override;
    virtual void sendLogInRequest(std::string username, std::string password) override;

    void sendGameSetup(std::string gameS); // TODO
    virtual void sendGameStarted() override;
    virtual void sendSaveGameRequest(std::string username) override;
    virtual void sendPauseRequest(std::string username) override;

    virtual void sendInvite(std::string aFriend) override;
    void joinGame(std::string gameSetup, int ELO, std::string username);
    void acceptFriendInvite(std::string username);

    virtual void sendFriendRequest(std::string receiver)  override;
    virtual void sendLeaderboardRequest()  override;

    virtual void sendDirectMessage(std::string sender, std::string receiver, std::string msg) override;
    virtual void sendGroupMessage(std::string sender, std::string msg, int gameId) override;

    virtual void sendDMChatBoxRequest(std::string sender, std::string receiver) override;
    
    /* ---- Sending Server Messages to The View/Model ---- */

    void processRequest(std::string message);

    void processAuth(std::string message);
    void processRelations(std::string message);
    void processResourceRequest(std::string message);
    void processChatbox(std::string message);
    void processGameSetup(std::string message);
    void processGameAction(std::string message);


    /**
     * @brief The servers sends an action (a pawn move) which was played by another player to the model and the view will update itself
     * 
     * @param action formatted in json
     */
    void movePlayerReceipt(std::string action);
    
    /**
     * @brief The servers sends an action (a wall placement) which was played by another player to the model and the view will update itself
     * 
     * @param action also formatted in json
     */
    void placeWallReceipt(std::string action);
    

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

    nlohmann::json logInReceipt(std::string msg);
    nlohmann::json registerReceipt(std::string msg);
    nlohmann::json friendRequestReceipt(std::string msg);

    nlohmann::json sendFriendsList(std::string msg);
    nlohmann::json sendfriendsRequestSentList(std::string msg);
    nlohmann::json sendfriendsRequestReceivedList(std::string msg);
    //  nlohmann::json sendChats(std::string msg);
    //  nlohmann::json sendGameIds(std::string msg);


    virtual bool isGameOver(bool over = false) override;
    
};