#include "MainModel.h"

auto MainModel::getUsername() const noexcept -> std::string *
{
    return m_username.get();
}

auto MainModel::getELO() const noexcept -> const float *
{
    return m_elo.get();
}

auto MainModel::isLoggedIn() const noexcept -> bool
{
    return m_isLoggedIn;
}

auto MainModel::getFriendList() const noexcept -> const std::vector<std::string> *
{
    return m_friendList.get();
}

auto MainModel::getFriendRequestsSent() const noexcept -> const std::vector<std::string> *
{
    return m_friendRequestsSent.get();
}

auto MainModel::getFriendRequestsReceived() const noexcept -> const std::vector<std::string> *
{
    return m_friendRequestsReceived.get();
}

auto MainModel::getChatWith(const std::string &username) const noexcept -> const std::vector<std::string> *
{
    return m_chats.at(username).get();
}

auto MainModel::getGameIDs() const noexcept -> const std::vector<int> *
{
    return m_gameIDs.get();
}
//
// auto MainModel::getCurrentGame() const noexcept -> const GameModel*
//{
//    return m_currentGame.get();
//}

auto MainModel::isPlayerTurn() const noexcept -> bool
{
    return m_isPlayerTurn;
}

auto MainModel::getLeaderboard() const noexcept -> const std::vector<std::pair<std::string, float>> *
{
    return m_leaderboard.get();
}

auto MainModel::isInGame() const noexcept -> bool
{
    return static_cast<bool>(m_currentGame);
}

auto MainModel::setUsername(const std::string &username) -> void
{
    m_username.reset(new std::string(username));
}
auto MainModel::setELO(const int &elo) -> void
{
    m_elo.reset(new float((float)elo));
}
auto MainModel::loginNotSuccessful() -> void
{
    m_isLoggedIn = false;
}

auto MainModel::loginSuccessful(const std::string & username) -> void
{
    m_username = std::make_shared<std::string>(username); // added A-M
    m_isLoggedIn = true;
}

auto MainModel::setFriendList(const std::vector<std::string> &friendList) -> void
{
    m_friendList.reset(new std::vector<std::string>(friendList));
}

auto MainModel::addFriend(const std::string &friendUsername) -> void
{
    m_friendList->push_back(friendUsername);
}

auto MainModel::setFriendRequestsSent(const std::vector<std::string> &friendRequestsSent) -> void
{
    m_friendRequestsSent.reset(new std::vector<std::string>(friendRequestsSent));
}

auto MainModel::addFriendRequestSent(const std::string &friendRequestSent) -> void
{
    m_friendList->push_back(friendRequestSent);
}

auto MainModel::setFriendRequestsReceived(const std::vector<std::string> &friendRequestsReceived) -> void
{
    m_friendRequestsReceived.reset(new std::vector<std::string>(friendRequestsReceived));
}

auto MainModel::addFriendRequestReceived(const std::string &friendRequestReceived) -> void
{
    m_friendRequestsReceived->push_back(friendRequestReceived);
}

auto MainModel::refuseFriendRequest(const std::string &notFriendUsername) -> void
{
    m_friendRequestsReceived->erase(
        std::remove(m_friendRequestsReceived->begin(), m_friendRequestsReceived->end(), notFriendUsername), m_friendRequestsReceived->end());
}

auto MainModel::removeFriend(const std::string &friendToRemove) -> void
{
    m_friendList->erase(std::remove(m_friendList->begin(), m_friendList->end(), friendToRemove), m_friendList->end());
}
auto MainModel::addFriendMessage(const std::string &friendUsername, const std::string &message) -> void
{
    m_chats[friendUsername]->push_back(message);
}

// auto MainModel::addGameMessage(const std::string &, const std::vector<std::string> &, const std::string &) -> void
//{
//
// }
auto MainModel::setLeaderboard(const std::vector<std::pair<std::string, float>> &leaderboard) -> void
{
    m_leaderboard.reset(new std::vector<std::pair<std::string, float>>(leaderboard));
}
