/**
 * @author Boris Petrov
 */

#pragma once

#include <string>
#include <vector>

using UserList = std::vector<std::string>;

enum class UserAttr {
    ELO,
    FriendList,
    FriendRequestsSent,
    FriendRequestsReceived,
};

/**
 * This is only a sort of intermediate interface between the
 * database and the UserHandler.
 */
class ServerUser
{
public:
    ServerUser()
    {
    }

    bool isLoggedIn() const noexcept;

    std::string getUsername() const noexcept;
    void bindToUsername(const std::string &);

    /**
     * This is to be called when a modification
     * was done to the DB.
     */
    void syncWithDB(UserAttr);

    // Getters
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

    int m_cachedELO;
    UserList m_cachedFriends;
    UserList m_cachedRequestsSent;
    UserList m_cachedRequestsReceived;
};
