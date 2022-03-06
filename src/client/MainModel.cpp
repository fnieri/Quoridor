#include "MainModel.h"

auto MainModel::getUsername() const noexcept -> *std::string
{
    return m_username.get();
}

auto MainModel::getELO() const noexcept -> *float
{
    return m_elo.get();
}

auto MainModel::isLoggedIn() const noexcept -> bool
{
    return m_isLoggedIn;
}

auto MainModel::getFriendList() const noexcept -> *std::vector<std::string>>
{
    return m_friendList.get();
}

auto MainModel::getFriendRequestsSent() const noexcept -> *std::vector<std::string>
{
    return m_friendRequestsSent.get();
}

auto MainModel::getFriendRequestsReceived() const noexcept -> *std::vector<std::string>
{
    return m_friendRequestsReceived.get();
}

auto MainModel::getChatWith(const std::string &username) const noexcept -> const *std::vector<std::string>
{
    return m_chats[username].get();
}

auto MainModel::getGameIDs() const noexcept -> *std::vector<int>
{
    return m_gameIDs.get();
}

auto MainModel::getCurrentGame() const noexcept -> *GameModel
{
    return m_currentGame.get();
}

auto MainModel::isPlayerTurn() const noexcept -> bool
{
    return m_isPlayerTurn;
}

auto MainModel::getLeaderboard() const noexcept -> *std::vector<std::pair<std::string, float>>
{
    return m_leaderboard.get();
}

auto MainModel::isInGame() const noexcept -> bool
{
    return static_cast<bool>(m_currentGame);
}