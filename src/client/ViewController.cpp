#include "Board.h"
#include "BoardComponent.h"
#include "Player.h"
#include "Point.h"
#include "WallEnum.h"
#include "ServerController.h"

#include <memory>
#include <vector>


ViewController::ViewController(std::shared_ptr<ServerController> serverController, int nPlayers) :
    serverController{serverController}, nPlayers{nPlayers}
{
}

/* Setters */ 

void ViewController::setBoard(std::shared_ptr<Board> theBoard) 
{
    board = theBoard;
}

void ViewController::setPlayers(std::vector<std::shared_ptr<Player>> thePlayers)
{
    players = thePlayers;
    nPlayers = players.size();
}

void ViewController::setGameSetup(std::string gameS)
{
    gameSetup = gameS;
}

/* To Game Model */ 

void ViewController::movePlayer(Point p)
{
    std::shared_ptr<PlayerAction> action {board, players[currentPlayerIndex], p / 2};
    if (action->executeAction() && !action->isGameOver())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers; // change turns if the PlayerAction is valid
    else if (action->isGameOver()) // SEND THIS TO WHO 
}

void ViewController::placeWall(Point p, WallOrientation orientation)
{
    std::shared_ptr<WallAction> action {board, players[currentPlayerIndex], p / 2, orientation};
    if (action->executeAction() && !action->isGameOver())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers; // change turns if the PlayerAction is valid
    else if (action->isGameOver()) // SEND THIS TO WHO
}

/* To Network Model */ 

void ViewController::startGame() 
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

    setBoard(board);
    setPlayers(players);
    serverController->setBoard(board);
    serverController->setPlayers(players);
}

void ViewController::saveGame() 
{
    serverController->saveGame();
}

void ViewController::pauseGame() 
{
    serverController->pauseGame();
}

void ViewController::registerPlayer(std::string username, std::string password)
{
    serverController->registerPlayer(username, password);
}

void ViewController::logIn(std::string username, std::string password)
{
    serverController->registerPlayer(username, password);
}

void ViewController::logOut()
{
    serverController->registerPlayer();
}

void ViewController::sendInvite(std::string aFriend, std::string gameSetup)
{
    serverController->sendInvite(aFriend, gameSetup);
}

void ViewController::joinGame(int gameId)
{
    serverController->joinGame(aFriend, gameSetup);
}

void ViewController::askToPause(std::string aFriend)
{
    serverController->askToPause(aFriend);
}

void ViewController::sendFriendRequest(std::string receiver)
{
    serverController->sendFriendRequest(receiver);
}

void ViewController::checkLeaderBoard()
{
    serverController->checkLeaderBoard();       // or call immediatly ELO and give to the view ?
}

/* To Chat Model */
void ViewController::sendMessage(std::string receiver, std::string msg)
{

}

void ViewController::sendMessage(std::string msg, int gameId)
{

}

void ViewController::receiveMessage(std::string receiver, std::string msg, int gameId)
{

}

void ViewController::loadMessages(std::string username)
{

}

void ViewController::loadMessages(int gameId)
{
}
