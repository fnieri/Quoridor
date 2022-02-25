#include "PlayerAction.h"

#include "PlayerEnum.h"

#include <iostream>
#include <memory>

using namespace std;
using json = nlohmann::json;

PlayerAction::PlayerAction(shared_ptr<Board> board, shared_ptr<Player> player, const Point &_destination)
    : board {board}
    , player {player}
//, destination {destination}
{
    destination = {_destination.x() * 2, _destination.y() * 2}; // Position in the matrix
}

bool PlayerAction::isActionValid()
{
    return board->isBasicMove(player->getMatrixPosition(), destination) || board->isJumpMove(player->getMatrixPosition(), destination)
        || board->isDiagonalMove(player->getMatrixPosition(), destination);
}

bool PlayerAction::isGameOver()
{
    return false;
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
