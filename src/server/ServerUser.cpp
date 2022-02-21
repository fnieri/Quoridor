/**
 * @author Boris Petrov
 */

#include "ServerUser.h"

#include <algorithm>

// TODO: make it work with db
//
// The setters here should all update the db.

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

void ServerUser::syncWithDB(UserAttr)
{
    // TODO ... the sync with the server
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
