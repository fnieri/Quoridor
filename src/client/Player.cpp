/**
* @file Player.h
* @author Nargis, Lèo, Anne-Marie
* @brief Class representing a Player in a game
* @date 2022-03-04
*
*/

#include "Player.h"
#include "PlayerEnum.h"

Player::Player(const PawnColors &color, const Point &position, const int &nwalls, const FinishLine &finishLine, const std::string &username)
    : color {color}
    , position {position}
    , nwalls {nwalls}
    , finishLine {finishLine}
    , username {username}
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

std::string Player::getUsername() const
{
    return username;
}

Player::~Player()
{
}
