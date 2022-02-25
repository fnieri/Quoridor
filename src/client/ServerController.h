/**
 * @file ServerController.h
 * @author your name (you@domain.com)
 * @brief Controller that gets messages from the Server and sends them to the correct Model and also sends messages to the Server gotten from the ViewController
 * @date 2022-02-25
 * 
*/

#pragma once

class ServerController
{
public:
    ServerController();

    /* To Game Model */
    void movePlayer(std::string action);
    void placeWall(std::string action);

    /* To Chat Model */
    void sendMessage(std::string receiver, std::string msg, int gameId);
    void receiveMessage(std::string receiver, std::string msg, int gameId);
    void loadMessages(std::string receiver);
    void loadMessages(int gameId);

    /* To Network Model */
    void startGame();
    void saveGame();
    void pauseGame();

    void sendFriendRequest(std::string receiver);
    void checkLeaderBoard();

    // - Multiplayers Games
    void sendInvite(std::string aFriend, std::string gameSetup);
    void joinGame(int gameId);
    void askPause(std::string aFriend); // a friend asks to pause

    // - Login
    void registerPlayer(std::string username, std::string password);
    void logIn(std::string username, std::string password);
    void logOut();
};