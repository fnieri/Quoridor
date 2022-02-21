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
    if (board->isPositionValid(p)) 
    {
        // if the player is trying to move his pawn
        if (board->isCell(p)) 
        {
            if (click_count == 0) 
            {   
                currentPlayer = whichPlayer(p); // jsp si c utile ou bien cmt on fait pr savoir qui est le current player ??
                first = p;
                ++click_count;
            }

            else if (board->isFree(p))
            {
                second = p;
                board->movePlayer(currentPlayer, second);
                --click_count;
            }
        }

        // if the player is trying to place a wall
        // we send the further left side cell or down side cell of the wall since a wall takes up 2 cells
        // do we care about who places it ? (to decrement the number of walls for a player ?)
        if (board->isCorridor(p) && board->isFree(p)) 
        {
            // board->placeWall(p, WHAT); ??
        }
    }
}


std::shared_ptr<Player> whichPlayer(Point p) 
{
    if (board->isCell(p))
    {
        if (!board->isFree(p))
        {
            // how find pointer to player
            // make function in board which gives pointer to board component
        }
    }
}
