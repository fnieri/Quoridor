/**
 * @file ServerController.h
 * @author Kourieh Anne-Marie
 * @brief Controller that gets messages from the Server and sends them to the correct Model and also sends messages to the Server gotten from the ViewController
 * @date 2022-02-25
 *
 */

#include <iostream>
#include <string>

#include "ViewController.h"

#pragma once

class ServerController
{
    std::shared_ptr<Board> board;
    std::shared_ptr<ViewController> viewController;
    int nPlayers;
    std::vector<std::shared_ptr<Player>> players;
    int currentGameId;
    std::string gameSetup;

    void makeDictPlayer();
    map<PawnColors, shared_ptr<Player>> dictPlayer;

public:
    ServerController(std::shared_ptr<ViewController> viewController);
    ~ServerController() = default;

    void setBoard(std::shared_ptr<Board> theBoard); 
    void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers); 
    void setDict(std::string dict_player);
    
    bool isGameOver(bool over);

    /* To Game Model */
    // send this to the viewcontroller ? but linking problems ?
    void movePlayer(std::string action);
    void placeWall(std::string action);

    /* To Network Model (the server) */
    void registerPlayer(std::string username, std::string password);
    void logIn(std::string username, std::string password);
    void logOut();

    void startGame();
    void saveGame();
    void pauseGame();

    void sendInvite(std::string aFriend, std::string gameSetup);
    void joinGame(int gameId);
    void askToPause(std::string aFriend); // a friend asks to pause

    void sendFriendRequest(std::string receiver);
    void checkLeaderBoard();

    /* To Chat Model (there isn't yet a chat model) */
    void sendDirectMessage(std::string receiver, std::string msg);
    void sendGroupMessage(std::string msg, int gameId);
    
    void receiveGroupMessage(std::string msg, int gameId);
    void receiveDirectMessage(std::string receiver, std::string msg, int gameId);
    
    void loadMessages(std::string username);
    void loadMessages(int gameId);
};