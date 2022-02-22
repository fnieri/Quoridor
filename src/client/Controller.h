#pragma once

#include <memory>
#include <vector>

class Controller
{
private:
    std::shared_ptr<Board> board;
    int click_count=0;
    int currentPlayerIndex=0;                           // index of the current player
    int nPlayers;                                       // number of players
    std::vector<std::shared_ptr<Player>> players;       // either 2 or 4 players
public:
    Controller(shared_ptr<Board> board);

    // Game functionalities
    void handleClickPlayer(Point p); 
    void handleClickWall(Point p);


    // Social functionalities
    void receiveMessage(std::string mess, std::string username, int gameId);
    void addFriend(std::string username, std::string friendUsername);
    // plenty others
};