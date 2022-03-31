#include "PlayerAction.h"

#include "PlayerEnum.h"

#include <nlohmann/json.hpp>

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
    }
    return false;
}

json PlayerAction::serialized()
{
    Point initialPosition = player->getPosition() * 2;

    int playerID = (int)player->getColor();

    json actionJson
        = {{"action_type", "player"}, {"initial_position", initialPosition.serialized()}, {"end_position", destination.serialized()}, {"player_id", playerID}};
    return actionJson;
}

Point PlayerAction::getDestination() const
{
    return destination;
}
