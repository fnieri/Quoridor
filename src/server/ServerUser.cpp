/**
 * @author Boris Petrov
 */

#include "ServerUser.h"
#include "Database.h"

#include <algorithm>

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

int ServerUser::getELO() noexcept
{
    m_cachedELO = DatabaseHandler::getELO(m_username);
    return m_cachedELO;
}

void ServerUser::setELO(int newELO)
{
    DatabaseHandler::setELO(m_username, newELO);
    m_cachedELO = newELO;
}

std::vector<std::string> ServerUser::getFriends() noexcept
{
    m_cachedFriends = DatabaseHandler::getFriends(m_username);
    return m_cachedFriends;
}

void ServerUser::addFriend(const std::string &newFriend)
{
    DatabaseHandler::addFriend(m_username, newFriend);
    m_cachedFriends.push_back(newFriend);
}

void ServerUser::removeFriend(const std::string &oldFriend)
{
    DatabaseHandler::removeFriend(m_username, oldFriend);
    try {
        m_cachedFriends.erase(std::find(m_cachedFriends.begin(), m_cachedFriends.end(), oldFriend)); // into oblivion
    } catch (std::exception &e) {
        // in case m_cachedFriends is empty
    }
}
