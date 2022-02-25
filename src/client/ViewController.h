#pragma once

#include <memory>
#include <vector>

// View Controller to easily send actions to the different models' controller : Game + Chat + Network
class ViewController
{
private:
    std::shared_ptr<Board> board;
    int nPlayers;                                       
    std::vector<std::shared_ptr<Player>> players; 
    int currentPlayerIndex=0;                           // index of the current player in the vector of Players
    int currentGameId;

public:
    ViewController(shared_ptr<Board> board, std::vector<std::shared_ptr<Player>> players, int nPlayers);

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

    /* To Network Model */
    void registerPlayer(std::string username, std::string password);
    void logIn(std::string username, std::string password);
    void logOut();

    void startGame();
    void saveGame();
    void pauseGame();

    void sendInvite(std::string aFriend, std::string gameSetup);      
    void joinGame(int gameId);      
    void askToPause(std::string aFriend);

    void sendFriendRequest(std::string receiver);      
    void checkLeaderBoard();

    /* To Chat Model */
    void sendMessage(std::string receiver, std::string msg);
    void sendMessage(std::string msg, int gameId);              
    void receiveMessage(std::string receiver, std::string msg, int gameId);           
    void loadMessages(std::string friendUsername);
    void loadMessages(int gameId);
};