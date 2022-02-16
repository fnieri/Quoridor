/**
 * @author Boris Petrov
 */

#include "ServerUser.h"

#include <algorithm>

// TODO: make it work with db

bool ServerUser::isLoggedIn() const noexcept
{
    return m_isLoggedIn;
}

std::string ServerUser::getUsername() const noexcept
{
    return m_username;
}

void ServerUser::bindToUsername(const std::string &username)
{
    m_username = username;
    m_isLoggedIn = true;
}

int ServerUser::getELO() const noexcept
{
    return m_cachedELO;
}

void ServerUser::setELO(int newELO)
{
    m_cachedELO = newELO;
}

std::vector<std::string> ServerUser::getFriends() const noexcept
{
    return m_cachedFriends;
}

void ServerUser::addFriend(const std::string &newFriend)
{
    m_cachedFriends.push_back(newFriend);
}

void ServerUser::removeFriend(const std::string &oldFriend)
{
    m_cachedFriends.erase(std::find(m_cachedFriends.begin(), m_cachedFriends.end(), oldFriend)); // into oblivion
}
