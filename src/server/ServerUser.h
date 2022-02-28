/**
 * @file ServerUser.h
 * @author Boris Petrov
 * @brief Representation of User on the server
 * @date 02/25/22
 */

#pragma once

#include <string>
#include <vector>

using UserList = std::vector<std::string>;

/**
 * Interface bewteen DB and UserHandler
 */
class ServerUser
{
public:
    ServerUser()
    {
    }

    /**
     * Whether the user is bound to a username from the DB
     */
    bool isLoggedIn() const noexcept;

    std::string getUsername() const noexcept;
    void bindToUsername(const std::string &);

    /**
     * Sync cached data with the DB
     *
     * @note This is to be called when a modification
     * was done to the DB.
     */
    void syncWithDB();

    // Getters of mutable data available on the DB
    int getELO() const noexcept;
    UserList getFriendList() const noexcept;
    UserList getFriendRequestsSent() const noexcept;
    UserList getFriendRequestsReceived() const noexcept;

    /**
     * Usually this is a json serialized message
     * that is of the following three types:
     *  - send friend request;
     *  - accept friend request;
     *  - remove friend.
     */
    /* void updateFriendRelations(const std::string &); */

private:
    bool m_isLoggedIn {false};
    std::string m_username;

    // Instead of always fetching data from the DB,
    // the data is stored locally and updated only
    // when the DB itself is modified.
    int m_cachedELO;
    UserList m_cachedFriends;
    UserList m_cachedRequestsSent;
    UserList m_cachedRequestsReceived;

    std::vector<int> m_cachedGameIds;
};
