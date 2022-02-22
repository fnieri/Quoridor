#include "Board.h"
#include "BoardComponent.h"
#include "Player.h"
#include "Point.h"
#include "WallEnum.h"

#include <memory>

Controller::Controller(std::shared_ptr<Board> board)
    : board {board} {}


void Controller::handleClick(Point p)
{
    if (board->isCell(p)) handleClickPlayer(p);         // voir en fonction de la réprésentation visuel faite par
    else (board->isCorridor(p)) handleClickWall(p);     // Léo et Sacha car problème de conversion sinon
}


void Controller::handleClickPlayer(Point p) 
{
    PlayerAction action{board, players[currentPlayerIndex], p};  // Question ? is p a position in the matrix or a position in the view of the players
    if (action.executeAction()) currentPlayerIndex = (currentPlayerIndex+1) % nPlayers;                    // because to remember : conversion or not ?
}

void Controller::handleClickWall(Point p) 
{
    // Elias
}