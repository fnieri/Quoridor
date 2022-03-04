/**
* @file PlayerAction.h
* @author Nargis, Lèo, Anne-Marie
* @brief Class representing a potential pawn-move action to be performed by a Player.
* @date 2022-03-04
*
* @see WallAction for the analogous action for wall placement.
 */


#include "PlayerAction.h"

#include "PlayerEnum.h"

#include <iostream>
#include <memory>

using namespace std;
using json = nlohmann::json;

PlayerAction::PlayerAction(shared_ptr<Board> board, shared_ptr<Player> player, const Point &_destination)
    : board {board}
    , player {player}
{
    destination = _destination * 2;
}

bool PlayerAction::isActionValid()
{
    return player->getMatrixPosition() != destination
        && (board->isValidBasicMove(player->getMatrixPosition(), destination) || board->isValidJumpMove(player->getMatrixPosition(), destination)
            || board->isValidDiagonalMove(player->getMatrixPosition(), destination));
}

bool PlayerAction::isGameOver()
{

    return board->isPositionOnFinishLine(player->getMatrixPosition(), player->getFinishLine());
}

bool PlayerAction::executeAction()
{

    if (isActionValid()) {
        board->movePlayer(player, destination);
        player->setMatrixPosition(destination);
        return true;
    } else
        return false;
}

json PlayerAction::serialized()
{
    Point initialPosition = player->getPosition();

    int playerID = (int)player->getColor();

    json actionJson = {{"initial_position", initialPosition.serialized()}, {"end_position", destination.serialized()}, {"player_id", playerID}};
    return actionJson;
}

PlayerAction::~PlayerAction()
{
}
