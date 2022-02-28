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
      // TODO sync gameids

      m_cachedELO = DatabaseHandler::getELO(m_username);
      m_cachedFriends = DatabaseHandler::getFriends(m_username);
      m_cachedRequestsSent = DatabaseHandler::getFriendRequestsSent(m_username);
      m_cachedRequestsReceived = DatabaseHandler::getFriendsRequestsReceived(m_username);
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

    // DatabaseHandler::removeFriend(m_username, oldFriend);
    //try {
    //    m_cachedFriends.erase(std::find(m_cachedFriends.begin(), m_cachedFriends.end(), oldFriend)); // into oblivion
    //} catch (std::exception &e) {
    //    // in case m_cachedFriends is empty
    //}

}
