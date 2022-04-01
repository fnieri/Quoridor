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

auto MainModel::getGameIDs() noexcept -> const std::map<int, std::vector<std::string>> *
{
    return m_gameIDs.get();
}
//
// auto MainModel::getCurrentGame() const noexcept -> const GameModel*
//{
//    return m_currentGame.get();
//}

// auto MainModel::isPlayerTurn() const noexcept -> bool
//{
//     return m_isPlayerTurn;
// }

auto MainModel::getLeaderboard() const noexcept -> const std::vector<std::pair<std::string, float>> *
{
    return m_leaderboard.get();
}

// auto MainModel::isInGame() const noexcept -> bool
//{
//     return static_cast<bool>(m_currentGame);
// }

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

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::addFriend(const std::string &friendUsername) -> void
{
    m_friendList->push_back(friendUsername);
    updateFriendsChatMap();

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::setFriendRequestsSent(const std::vector<std::string> &friendRequestsSent) -> void
{
    updatePtrValue(m_friendRequestsSent, friendRequestsSent);

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::addFriendRequestSent(const std::string &friendRequestSent) -> void
{
    m_friendList->push_back(friendRequestSent);

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::setFriendRequestsReceived(const std::vector<std::string> &friendRequestsReceived) -> void
{
    updatePtrValue(m_friendRequestsReceived, friendRequestsReceived);

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::addFriendRequestReceived(const std::string &friendRequestReceived) -> void
{
    m_friendRequestsReceived->push_back(friendRequestReceived);

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::acceptFriendRequest(const std::string &friendUsername) -> void
{
    m_friendRequestsSent->erase(std::remove(m_friendRequestsSent->begin(), m_friendRequestsSent->end(), friendUsername), m_friendRequestsSent->end());
    addFriend(friendUsername);

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::refuseFriendRequest(const std::string &notFriendUsername) -> void
{
    m_friendRequestsSent->erase(std::remove(m_friendRequestsSent->begin(), m_friendRequestsSent->end(), notFriendUsername), m_friendRequestsSent->end());

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::removeFriend(const std::string &friendToRemove) -> void
{
    m_friendList->erase(std::remove(m_friendList->begin(), m_friendList->end(), friendToRemove), m_friendList->end());

    notifyObservers(QuoridorEvent::RelationsModified);
}

auto MainModel::addFriendMessage(const std::string &friendUsername, const Message &msg) -> void
{
    if (m_chats.find(friendUsername) == m_chats.end()) {
        m_chats.insert({friendUsername, std::make_shared<std::vector<Message>>()});
    }
    m_chats.at(friendUsername)->push_back(msg);

    notifyObservers(QuoridorEvent::ChatsModified);
}

// auto MainModel::addGameMessage(const std::string &sender, const std::vector<std::string> &players, const std::string &message) -> void
//{
//     m_chats[riendUsername]->push_back({friendUsername, message});
// notifyObservers(QuoridorEvent::GameChatUpdated);
//
// }

auto MainModel::setLeaderboard(const std::vector<std::pair<std::string, float>> &leaderboard) -> void
{
    updatePtrValue(m_leaderboard, leaderboard);
    notifyObservers(QuoridorEvent::LeaderboardModified);
}

auto MainModel::setGameIds(const std::map<int, std::vector<std::string>> &gameIDs) -> void
{
    updatePtrValue(m_gameIDs, gameIDs);
    notifyObservers(QuoridorEvent::GameIdsUpdated);
}

auto MainModel::updateFriendsChatMap() noexcept -> void
{
    if (!hasFriends)
        m_chats.clear();
    for (auto &friendUsername : *m_friendList) {
        if (m_chats.find(friendUsername) == m_chats.end()) {
            m_chats[friendUsername] = std::make_shared<std::vector<Message>>();
        }
    }
    notifyObservers(QuoridorEvent::FriendsUpdated);
}

auto MainModel::clearFriendMessages(const std::string &friendUsername) -> void
{
    if (m_chats.find(friendUsername) != m_chats.end()) {
        m_chats.erase(friendUsername);
    }
}
auto MainModel::getHasFriends() const noexcept -> bool
{
    return hasFriends;
}

auto MainModel::setHasFriends(const bool &val) -> void
{
    hasFriends = val;
}

auto MainModel::getCurrentGame() -> GameModel *
{
    return m_currentGame.get();
}

auto MainModel::isInGame() const noexcept -> bool
{
    return static_cast<bool>(m_currentGame);
}

auto MainModel::loadGame(const std::string &boardConfig) noexcept -> void
{
    m_currentGame = std::make_shared<GameModel>(boardConfig);
    notifyObservers(QuoridorEvent::GameUpdated);
}

auto MainModel::unloadGame() -> void
{
    m_currentGame.reset();
}

auto MainModel::hasFriendNotification() const noexcept -> bool
{
    return m_friendNotification;
}

auto MainModel::hasGameNotification() const noexcept -> bool
{
    return m_gameNotification;
}

auto MainModel::setFriendNotification(const bool &val) -> void
{
    m_friendNotification = val;
}

auto MainModel::setGameNotification(const bool &val) -> void
{
    m_gameNotification = val;
}

auto MainModel::createAiGame() noexcept -> void
{
    std::vector<std::string> p_players {"player", "ai"};
    setUsername(p_players[0]);
    updatePtrValue(m_currentGame, AiGameModel {p_players});
}

auto MainModel::addGameId(const int &gId, const std::vector<std::string> &players) -> void
{
    m_gameIDs->insert({gId, players});
    notifyObservers(QuoridorEvent::GameIdsUpdated);
}

auto MainModel::isGameStarted() const noexcept -> bool
{
    return m_isGameStarted;
}

auto MainModel::setIsGameStarted(const bool &val) -> void
{
    m_isGameStarted = val;
}

auto MainModel::processGameAction(const std::string &serAction) -> void
{
    m_currentGame->processAction(serAction);
    notifyObservers(QuoridorEvent::GameUpdated);
}

auto MainModel::playerSurrended(const std::string &username) -> void
{
    m_currentGame->playerSurrended(username);
}
