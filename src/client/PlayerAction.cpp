#include "PlayerAction.h"

#include "PlayerEnum.h"

#include <iostream>
#include <memory>

using namespace std;
using json = nlohmann::json;

PlayerAction::PlayerAction(shared_ptr<Board> board, shared_ptr<Player> player, const Point &destination)
    : board {board}
    , player {player}
    , destination {destination}
{
}

bool PlayerAction::isActionValid()
{
    // Check if the position is occupied or......
    return false;
}

bool PlayerAction::isGameOver()
{
    return false;
}

bool PlayerAction::executeAction()
{
    return false;

    // board->movePlayer()
}

json PlayerAction::serialized()
{
    Point initialPosition = player->getPosition();

    int playerID = (int)player->getColor();

    json actionJson = {{"initial_position", initialPosition.serialized()}, {"end_position", destination.serialized()}, {"player_id", playerID}};
    return actionJson;
}

void setIndex(int ind)
{
    index = ind;
}

int getIndex()
{
    return index;
}

PlayerAction::~PlayerAction()
{
}
