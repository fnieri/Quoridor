/**
 * @file main.cpp
 * @author Kourieh Anne-Marie (and Gamboa Dos Santos Léo)
 * @brief main.cpp plays the game when the player clicks on start game (Idea but don't know how to call this)
 * @date 2022-02-25
*/

#include "Board.h"
#include "Player.h"
#include "PlayerAction.h"
#include "Point.h"
#include "ViewController.h"
#include "ServerController.h"


#include <memory>
#include <vector>
/*
int main(int nPlayers, std::string gameSetup, std::shared_ptr<ViewController> viewController, std::shared_ptr<ServerController> serverController,)
{   
    
    std::shared_ptr<Board> board;
    std::vector<std::shared_ptr<Player>> players;

    for (int i = 0; i < nPlayers; i++) 
    {
        // TODO: Change spawn position of players
        Point pos{i, i};
        auto p = std::make_shared<Player>(PawnColors(i), pos, 10);

        players.push_back(p);

        // Temporary way of adding the players to the board
        PlayerAction spawnPlayer {board, p, pos};
        spawnPlayer.executeAction();
    }

    viewController->setBoard(board);
    viewController->setPlayers(players);
    serverController->setBoard(board);
    serverController->setPlayers(players);
    

    return 0;
}
*/

int main() {
    return 0;
}