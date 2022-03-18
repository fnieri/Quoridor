#include "MainModel.h"

#include <utility>

template <typename P, typename V>
auto MainModel::updatePtrValue(P &ptr, V value) const noexcept -> void
{
    if (ptr) {
        *ptr = value;
    } else {
        ptr = std::make_shared<V>(value);
    }
}

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

auto MainModel::getChatWith(const std::string &username) noexcept -> SPtrToVec<Message>
{
    if (m_chats.find(username) == m_chats.end()) {
        m_chats.insert({username, std::make_shared<std::vector<Message>>()});
    }
    return m_chats.at(username);
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
    updatePtrValue(m_username, username);
    m_isLoggedIn = true;
}
auto MainModel::setElo(const float &elo) -> void
{
    updatePtrValue(m_elo, elo);
}
auto MainModel::loginNotSuccessful() -> void
{
    m_isLoggedIn = false;
}

auto MainModel::loginSuccessful(const std::string &username) -> void
{
    m_isLoggedIn = true;
    setUsername(username);
}

auto MainModel::setFriendList(const std::vector<std::string> &friendList) -> void
{
    updatePtrValue(m_friendList, friendList);
    updateFriendsChatMap();
}

auto MainModel::addFriend(const std::string &friendUsername) -> void
{
    m_friendList->push_back(friendUsername);
    updateFriendsChatMap();
}

auto MainModel::setFriendRequestsSent(const std::vector<std::string> &friendRequestsSent) -> void
{
    updatePtrValue(m_friendRequestsSent, friendRequestsSent);
}

auto MainModel::addFriendRequestSent(const std::string &friendRequestSent) -> void
{
    m_friendList->push_back(friendRequestSent);
}

auto MainModel::setFriendRequestsReceived(const std::vector<std::string> &friendRequestsReceived) -> void
{
    updatePtrValue(m_friendRequestsReceived, friendRequestsReceived);
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

auto MainModel::addFriendMessage(const std::string &friendUsername, const Message &msg) -> void
{
    if (m_chats.find(friendUsername) == m_chats.end()) {
        m_chats.insert({friendUsername, std::make_shared<std::vector<Message>>()});
    }
    m_chats.at(friendUsername)->push_back(msg);
}

// auto MainModel::addGameMessage(const std::string &sender, const std::vector<std::string> &players, const std::string &message) -> void
//{
//     m_chats[riendUsername]->push_back({friendUsername, message});
//
// }

auto MainModel::setLeaderboard(const std::vector<std::pair<std::string, float>> &leaderboard) -> void
{
    updatePtrValue(m_leaderboard, leaderboard);
}

auto MainModel::setGameIds(const std::vector<int> &gameIDs) -> void
{
    updatePtrValue(m_gameIDs, gameIDs);
}

auto MainModel::updateFriendsChatMap() noexcept -> void
{
    for (auto &friendUsername : *m_friendList) {
        if (m_chats.find(friendUsername) == m_chats.end()) {
            m_chats[friendUsername] = std::make_shared<std::vector<Message>>();
        }
    }
}
auto MainModel::clearFriendMessages(const std::string &friendUsername) -> void
{
    if (m_chats.find(friendUsername) != m_chats.end()) {
        m_chats.erase(friendUsername);
    }
}

GameModel::GameModel(int gameId, std::vector<std::string> players, std::shared_ptr<Board> board)
    : m_gameId(gameId)
    , m_players(std::move(players))
    , m_board(std::move(board))
{
}

auto GameModel::getCurrentPlayer() noexcept -> int *
{
    return &currentPlayerIdx;
}

auto GameModel::isMoveValid(const Point &movePoint) const noexcept -> bool
{
    //    PlayerAction move {board, players.at(currentPlayerIndex), movePoint/2};
    //    return move.isActionValid();
}
