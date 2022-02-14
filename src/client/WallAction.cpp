#include "WallAction.h"
#include "Board.h"
#include "Player.h"

#include <memory>

using namespace std;

WallAction::WallAction(shared_ptr<Board> board, shared_ptr<Player> player, const Point &destCell, const WallOrientation &orientation)
    : board {board}
    , player {player}
    , destCell {destCell}
    , orientation {orientation}
{
}

WallAction::~WallAction()
{
}

bool WallAction::isWallPlacementLegal()
{
    // Check if the placement doesn't block the other players
    return false;
}

bool WallAction::isWallPlacementValid()
{
    // Check if the corridors where we put our walls are not occupied
    // and the player has walls left to place
    return false;
}

bool WallAction::executeAction()
{
    return false;

    // board->placeWall()
    //  if isWallPlacementValid() and isWallPlacementLegal()
    //   {
    // board->placeWall;
    //  return true;
    //  }
}