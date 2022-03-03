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
#include "ViewController.h"
#include "ServerBridge.h"


class ViewController;
class ServerBridge;

class ServerController
{
    std::shared_ptr<Board> board = std::make_shared<Board>();;                       // The Game Model
    int nPlayers;                                       // The Number of Players
    std::vector<std::shared_ptr<Player>> players;       // A vector containing pointers to all the Players 
    std::map<PawnColors, std::shared_ptr<Player>> dictPlayer;   // A map with Colors of a player's pawn and the corresponding Player
    std::shared_ptr<ViewController> viewController;
    ServerBridge serverBridge{"localhost", 12345};  

public:
    ServerController();
    ~ServerController() = default;

    /* Setters */
    
     void setBoard(std::shared_ptr<Board> aBoard) ; 

     void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers) ; 
    
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

    void sendRegisterRequest(std::string username, std::string password);
    void sendLogInRequest(std::string username, std::string password);

    void sendGameSetup(std::string gameS); // TODO
    void sendGameStarted();
    void sendSaveGameRequest(std::string username);
    void sendPauseRequest(std::string username);

    void sendInvite(std::string aFriend);
    void joinGame(std::string gameSetup, int ELO, std::string username);
    void acceptFriendInvite(std::string username);

    void sendFriendRequest(std::string sender, std::string receiver);
    void sendLeaderboardRequest();

     void sendDirectMessage(std::string sender, std::string receiver, std::string msg) ;
     void sendGroupMessage(std::string sender, std::string msg, int gameId) ;

    void sendDMChatBoxRequest(std::string sender, std::string receiver);
    
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
    
    void receiveGroupMessage(std::string msg);
    
    void receiveDirectMessage(std::string msg);

    void logInReceipt(std::string msg);
    void registerReceipt(std::string msg);
    void friendRequestReceipt(std::string msg);

    void sendFriendsList(std::string msg);
    void sendfriendsRequestSentList(std::string msg);
    void sendfriendsRequestReceivedList(std::string msg);
    //  nlohmann::json sendChats(std::string msg);
    //  nlohmann::json sendGameIds(std::string msg);


     bool isGameOver(bool over = false) ;
    
};