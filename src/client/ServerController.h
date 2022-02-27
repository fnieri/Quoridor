/**
 * @file ServerController.h
 * @author Kourieh Anne-Marie
 * @brief Controller that gets messages from the Server and sends them to the correct Model and also sends messages to the Server gotten from the ViewController
 * @date 2022-02-25
 *
 */

#pragma once

using json = nlohmann::json;

class ServerController
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

    void setBoard(std::shared_ptr<Board> theBoard); 
    void setPlayers(std::vector<std::shared_ptr<Player>> thePlayers);
    void setDict(std::map<PawnColors, std::shared_ptr<Player>> dict_play);

    bool isGameOver(bool over);

    /* To Game Model */
    void movePlayer(std::string action);
    void placeWall(std::string action);

    /* To Network Model (the server) */
    void registerPlayer(std::string username, std::string password);
    void logIn(std::string username, std::string password);
    void logOut();

    void startGame();
    void saveGame(std::string username);
    void pauseGame(std::string username);

    void sendInvite(std::string aFriend, std::string gameSetup);
    void joinGame(int gameId);
    void askToPause(std::string aFriend); // a friend asks to pause

    void sendFriendRequest(std::string receiver);
    void checkLeaderBoard();

    /* To Chat Model (there isn't yet a chat model) */

    bool isDirectMessageReceived(bool received = false);
    bool isGroupMessageReceived(bool received = false);

    void sendDirectMessage(std::string sender, std::string receiver, std::string msg);
    void sendGroupMessage(std::string sender, std::string msg, int gameId);

    json receiveGroupMessage(std::string msg);
    json receiveDirectMessage(std::string msg);

    void loadDirectMessages(std::string username);
    void loadGroupMessages(int gameId);
};