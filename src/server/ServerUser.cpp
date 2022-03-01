/**
 * @file ServerUser.cpp
 * @author Boris Petrov
 * @brief Representation of User on the server
 * @date 02/25/22
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

void ServerUser::syncWithDB()
{
      m_cachedELO = DatabaseHandler::getELO(m_username);
      m_cachedFriends = DatabaseHandler::getFriends(m_username);
      m_cachedRequestsSent = DatabaseHandler::getSentFriendRequests(m_username);
      m_cachedRequestsReceived = DatabaseHandler::getReceivedFriendRequests(m_username);
      /* m_cachedGameIds = DatabaseHandler::getGameIds(m_username); */
}

int ServerUser::getELO() const noexcept
{
    return m_cachedELO;
}

UserList ServerUser::getFriendList() const noexcept
{
    return m_cachedFriends;
}

UserList ServerUser::getFriendRequestsSent() const noexcept
{
    return m_cachedRequestsSent;
}

UserList ServerUser::getFriendRequestsReceived() const noexcept
{
    return m_cachedRequestsReceived;
}
