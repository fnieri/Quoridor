#include "Player.h"

Player::Player(const PawnColors &color, Point &position, int &nwalls)
    : color {color}
    , position {position}
{
}

Player::~Player()
{
}

