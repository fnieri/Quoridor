#pragma once

#include <memory>

class Controller
{
private:
    std::shared_ptr<Board> board;
    int click_count=0;
    Point first;
    Point second;
    std::shared_ptr<Player> currentPlayer;
    std::shared_ptr<Player> whichPlayer(Point p);       // 1st player is white 
public:
    Controller(shared_ptr<Board> board);

    // Game functionalities
    void handleClick(Point p);

    // Social functionalities
    void receiveMessage(std::string mess, std::string username, int gameId);
    void addFriend(std::string username, std::string friendUsername);

};