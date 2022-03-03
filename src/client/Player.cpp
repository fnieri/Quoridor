#include "Player.h"
#include "PlayerEnum.h"

Player::Player(const PawnColors &color, const Point &position, const int &nwalls, const FinishLine &finishLine)
    : color {color}
    , position {position}
    , nwalls {nwalls}
    , finishLine {finishLine}
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

void Player::setMatrixPosition(const Point &newPosition)
{
    setPosition(newPosition / 2);
}

Point Player::getPosition() const
{
    return position;
}

Point Player::getMatrixPosition() const
{
    return getPosition() * 2;
}

FinishLine Player::getFinishLine() const
{
    return finishLine;
}

int Player::nWalls() const
{
    return nwalls;
}

void Player::takeAwayWall()
{
    nwalls--;
}

PawnColors Player::getColor()
{
    return color;
}

void Player::setColor(PawnColors newColor)
{
    color = newColor;
}

Player::~Player()
{
}

void Player::setIndex(int ind)
{
    index = ind;
}

int Player::getIndex()
{
    return index;
}