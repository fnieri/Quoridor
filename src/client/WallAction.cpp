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
    // Check if the wall placement is valid / authorized by the rules (player path excluded)

    // Check if the player has enough wall remaining
    if (player->nWalls() <= 0)
        return false;

    // Check that the wall doesn't land out of bounds
    if (destCell.x() < 0 || destCell.y() < 0 || destCell.x() >= board->getCellSize() - 1 || destCell.y() >= board->getCellSize() - 1)
        return false;

    int x = destCell.x() * 2;
    int y = destCell.y() * 2;

    // Check that the middle piece is free (to avoid intersecting walls)
    if (!board->isFree(Point {x + 1, y + 1}))
        return false;

    // Check that both wall pieces don't interesect, for vertical walls and horizontal walls
    if (orientation == WallOrientation::Vertical && board->isFree(Point {x + 1, y}) && board->isFree(Point {x + 1, y + 2})) {
        return true;
    } else if (board->isFree(Point {x, y + 1}) && board->isFree(Point {x + 2, y + 1})) {
        return true;
    }

    return false;
}

bool WallAction::executeAction()
{
    if (isWallPlacementValid() && isWallPlacementLegal()) {
        board->placeWall(destCell, orientation);
        player->takeAwayWall();
    } else {
        return false;
    }
}