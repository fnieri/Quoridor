#include "PlayerAction.h"

#include <memory>

using namespace std;

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

PlayerAction::~PlayerAction()
{
}
