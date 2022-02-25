#include "Board.h"
#include "BoardComponent.h"
#include "Player.h"
#include "Point.h"
#include "WallEnum.h"

#include <memory>

ViewController::ViewController(std::shared_ptr<Board> board, std::vector<std::shared_ptr<Player>> players, int nPlayers)
    : board{board}, players{players}, nPlayers{nPlayers} { nPlayers = players.size(); }


void ViewController::movePlayer(Point p) 
{
    std::shared_ptr<PlayerAction> action{board, players[currentPlayerIndex], p/2};
    if (action->executeAction()) currentPlayerIndex = (currentPlayerIndex+1) % nPlayers;          // change turns if the PlayerAction is valid
}

void ViewController::placeWall(Point p, WallOrientation orientation)
{
    std::shared_ptr<WallAction> action{board, players[currentPlayerIndex], p/2, orientation};
    if (action->executeAction()) currentPlayerIndex = (currentPlayerIndex+1) % nPlayers;          // change turns if the PlayerAction is valid
}