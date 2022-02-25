/**
 * @file ViewController.h
 * @author Kourieh Anne-Marie
 * @brief Controller that gets messages from the View and sends them to the correct Model
 * @date 2022-02-25
 * 
*/

#pragma once


#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "WallEnum.h"
#include "ServerController.h"

#include <memory>
#include <vector>

// View Controller to easily send actions to the different models' controller : Game + Chat + Network
class ViewController
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
    ViewController();
    ~ViewController() = default;

    /* Setters */
    void setBoard(std::shared_ptr<Board> aBoard);
    void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers);

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
    void registerPlayer(std::string username, std::string password);
    void logIn(std::string username, std::string password);
    void logOut();

    void setGameSetup(std::string gameS);
    void startGame();
    void saveGame();
    void pauseGame();

    void sendInvite(std::string aFriend, std::string gameSetup);
    void joinGame(int gameId);
    void askToPause(std::string aFriend);

    void sendFriendRequest(std::string receiver);
    void checkLeaderBoard();

    /* To Chat Model (there isn't yet a chat model) */
    void sendMessage(std::string receiver, std::string msg);
    void sendMessage(std::string msg, int gameId);
    void receiveMessage(std::string receiver, std::string msg, int gameId);
    void loadMessages(std::string username);
    void loadMessages(int gameId);
};