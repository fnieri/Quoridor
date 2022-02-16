/**
 * @author Boris Petrov
 */

#pragma once

#include <string>
#include <vector>

/**
 * The setters here should also update the entries
 * related in the database.
 *
 * For instance, setting the elo should modify the cached
 * value but also the one in the database.
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

    int getELO() const noexcept;
    void setELO(int);

    std::vector<std::string> getFriends() const noexcept;
    void addFriend(const std::string &);
    void removeFriend(const std::string &);

private:
    bool m_isLoggedIn {false};
    std::string m_username;
    int m_cachedELO;
    std::vector<std::string> m_cachedFriends;
};
