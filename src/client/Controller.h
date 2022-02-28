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
    virtual void setBoard(std::shared_ptr<Board> aBoard)=0;
    virtual void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers)=0;

    /* To Network Model */ 
    virtual void registerPlayer(std::string username, std::string password)=0;
    virtual void logIn(std::string username, std::string password)=0;
    virtual void logOut()=0;

    virtual void startGame()=0;
    virtual void saveGame(std::string username)=0;
    virtual void pauseGame(std::string username)=0;

    virtual void sendInvite(std::string aFriend, std::string gameSetup)=0;
    virtual void joinGame(int gameId)=0;
    virtual void askToPause(std::string aFriend)=0;

    virtual void sendFriendRequest(std::string receiver)=0;
    virtual void checkLeaderBoard()=0;

    /* To Chat Model */
    virtual void sendDirectMessage(std::string sender, std::string receiver, std::string msg)=0;
    virtual void sendGroupMessage(std::string sender, std::string msg, int gameId)=0;

    virtual bool isDirectMessageReceived(bool received = false)=0;
    virtual bool isGroupMessageReceived(bool received = false)=0;

    virtual void loadDirectMessages(std::string username)=0;
    virtual void loadGroupMessages(int gameId)=0;

    /* Noticing the view */
    virtual bool isGameOver(bool over = false)=0;
};