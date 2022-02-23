#include "Controller.h"
#include "Board.h"
#include "BoardComponent.h"
#include "Player.h"
#include "PlayerAction.h"
#include "Point.h"
#include "WallAction.h"
#include "WallEnum.h"

#include <memory>

Controller::Controller(std::shared_ptr<Board> board)
    : board {board}
{
    for (int i = 0; i < nPlayers; i++) {
        // TODO: Change default position of players
        players.push_back(Player {PawnColors(i), Point {0, 0}, 10});
    }
    //the controller should create the view here
}

void Controller::handleClick(Point p)
{
    if (board->isCell(p))
        handleClickPlayer(p); // voir en fonction de la réprésentation visuel faite par
    else if (board->isCorridor(p))
        handleClickWall(p); // Léo et Sacha car problème de conversion sinon
}


void Controller::handleClickPlayer(Point p) 
{
    PlayerAction action{board, players[currentPlayerIndex], p};  // Question ? is p a position in the matrix or a position in the view of the players
    if (action.executeAction()) currentPlayerIndex = (currentPlayerIndex+1) % nPlayers;                    // because to remember : conversion or not ?
}

void Controller::handleClickWall(Point p) 
{
    //how do we determine the orientation here in order to create an instance of Wallaction? My proposition is to have derive the orientation in Wallaction by 
    //the coridor that correspond to the point or derive it in handle click by checking whether p.x is even or not
    WallAction action {board, players[currentPlayerIndex], p, board->isEven(p.x()) ? WallOrientation::Horizontal : WallOrientation::Vertical};
    if (action.executeAction()) currentPlayerIndex = (currentPlayerIndex+1) % nPlayers;
}