/**
 * @file Controller.h
 * @author Kourieh Anne-Marie
 * @brief Abstract Class for Controllers
 * @date 2022-02-28
 * 
*/

#pragma once

#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "WallAction.h"

class Controller
{
public:
    /* Setters */
    /**
     * @brief Set the Board object
     * 
     * @param aBoard the board given
     */
    virtual void setBoard(std::shared_ptr<Board> aBoard)=0;

    /**
     * @brief Set the Players object
     * 
     * @param thePlayers the vector of Players given
     */
    virtual void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers)=0;

    /* ---- To Network Model ---- */
    /**
     * @brief When a player wants to register, the view sends their wanted username and password which will be sent to the Server
     * 
     * @param username 
     * @param password 
     */
    virtual void registerPlayer(std::string username, std::string password)=0;
    
    /**
     * @brief When a player wants to log themself in, the view sends their username and password which will be checked by the Server
     * 
     * @param username 
     * @param password 
     */
    virtual void logIn(std::string username, std::string password)=0;
    
    /**
     * @brief A player wants to log out so we send this message to the server
     * 
     */
    virtual void logOut()=0;

    /**
     * @brief When the player clicks on Start, we initialize everything to set up the game
     * 
     */
    virtual void startGame()=0;

    /**
     * @brief The player clicks on Save, we send this demand to the Server
     * 
     * @param username the corresponding username of the player
     */
    virtual void saveGame(std::string username)=0;
    
    /**
     * @brief The player clicks on Pause, we send this demand to the Server
     * 
     * @param username the corresponding username of the player
     */
    virtual void pauseGame(std::string username)=0;

    /**
     * @brief Sending invites to another friend to play a multiplayer game with the help of the Server
     * 
     * @param aFriend the friend who we sent the invite to
     * @param gameSetup the setup of the game wanted
     */
    virtual void sendInvite(std::string aFriend, std::string gameSetup)=0;
    
    /**
     * @brief A player wants to join a game with its given Game ID and the request is sent to the Server
     * 
     * @param gameId 
     */
    virtual void joinGame(int gameId)=0;

    /**
     * @brief In a Multiplayer Game, if somebody asks to pause the game we have to send a request to the Server which will handle the pause on each player's own machine
     * 
     * @param aFriend the username of the friend who asked to pause
     */
    virtual void askToPause(std::string aFriend)=0;

    /**
     * @brief Sending a friend request to another player
     * 
     * @param receiver the friend we want to add
     */
    virtual void sendFriendRequest(std::string receiver)=0;
    
    /**
     * @brief If a player wants to check the Leaderboard, we send it to the View after receiving it from the Server
     * 
     */
    virtual void checkLeaderBoard()=0;

    /* ---- To Chat Model ---- */
    
    /**
     * @brief Sending a message written in a Two Person Chatbox to the Server
     * 
     * @param sender the username of the person who wrote the message
     * @param receiver the username of the person who will receive it
     * @param msg the message itself
     */
    virtual void sendDirectMessage(std::string sender, std::string receiver, std::string msg)=0;
    
    /**
     * @brief Sending a message written in a Group Chatbox when playing a Multiplayer Game to the Server
     * 
     * @param sender the username of the person who wrote the message
     * @param msg the message
     * @param gameId the ID of the game currently played 
     */
    virtual void sendGroupMessage(std::string sender, std::string msg, int gameId)=0;

    /**
     * @brief Asks the Server to load all the messages between two person
     * 
     * @param username the username of the friend's DM
     */
    virtual void loadDirectMessages(std::string username)=0;
    
    /**
     * @brief Asks the Server to load all the messages between players in a Multiplayer Game
     * 
     * @param gameID the ID of the Multiplayer Game
     */
    virtual void loadGroupMessages(int gameId)=0;

    /* Notify the view */
    
    /**
     * @brief A function serving as a notifiyer to the View/Server when wanting to check if the current Game is over or not
     * 
     * @param over the boolean received (set to default)
     * @return true 
     * @return false 
     */
    virtual bool isGameOver(bool over = false)=0;

    /**
     * @brief A function serving as a notifiyer to the View/Server when wanting to check if a message is received in Direct Message
     * 
     * @param received a boolean set to false by default
     * @return true 
     * @return false 
     */
    virtual bool isDirectMessageReceived(bool received = false)=0;
    
    /**
     * @brief A function serving as a notifiyer to the View/Server when wanting to check if a message is received in a Group Chatbox
     * 
     * @param received a boolean set to false by default
     * @return true 
     * @return false 
     */
    virtual bool isGroupMessageReceived(bool received = false)=0;

};