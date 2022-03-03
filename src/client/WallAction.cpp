#include "WallAction.h"
#include "Board.h"
#include "Player.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace std;
using json = nlohmann::json;

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

Point WallAction::piece1()
{
    if (orientation == WallOrientation::Vertical) {
        return Point {destCell.x() * 2 + 1, destCell.y() * 2};
    } else {
        return Point {destCell.x() * 2, destCell.y() * 2 + 1};
    }
}

Point WallAction::piece2()
{
    if (orientation == WallOrientation::Vertical) {
        return Point {destCell.x() * 2 + 1, destCell.y() * 2 + 2};
    } else {
        return Point {destCell.x() * 2 + 2, destCell.y() * 2 + 1};
    }
}

bool WallAction::isWallPlacementLegal()
{
    // Check if the placement doesn't block the other players

    std::vector<std::shared_ptr<Player>> players = board->findPlayers();

    for (auto &p : players) {
        if (!board->pathExists(p->getPosition(), p->getFinishLine(), piece1(), piece2()))
            return false;
    }

    return true;
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
    if (board->isFree(piece1()) && board->isFree(piece2())) {
        return true;
    }

    return false;
}

bool WallAction::executeAction()
{
    if (isWallPlacementValid() && isWallPlacementLegal()) {
        board->placeWall(destCell, orientation);
        player->takeAwayWall();
        return true;
    }

    return false;
}

// We'll surely have to change this to play Quotetris
json WallAction::serialized()
{
    int playerID = (int)player->getColor();
    json wallJson = {{"wall_cell", destCell.serialized()}, {"wall_orientation", toJsonOutput(orientation)}, {"player_id", playerID}};
    return wallJson;
}
