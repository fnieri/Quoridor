#include "Player.h"

Player::Player(const PawnColors &color, const Point &position, const int &nwalls)
    : color {color}
    , position {position}
    , nwalls {nwalls}
{
}

Player::~Player()
{
}

