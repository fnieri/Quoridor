#include "Player.h"

Player::Player(const PawnColors &color, const Point &position, const int &nwalls)
    : color {color}
    , position {position}
    , nwalls {nwalls}
{
}

int Player::x() const
{
    return position.x();
}

int Player::y() const
{
    return position.y();
}

void Player::setPosition(const Point &newPosition)
{
    position = newPosition;
}

Player::~Player()
{
}
