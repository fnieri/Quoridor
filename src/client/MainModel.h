#pragma once

#include "Board.h"
#include "BoardComponent.h"
#include "Cell.h"
#include "Corridor.h"
#include "GameModel.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerEnum.h"
#include "ServerBridge.h"
#include "WallAction.h"
#include "WallEnum.h"
#include "src/common/Message.h"
#include "src/common/MessageEnums/DataTypes.h"
#include "src/common/MessageEnums/Domain.h"
#include "src/common/Observer.h"
#include "src/common/Point.h"
#include "src/common/SerializableMessageFactory.h"

#include <map>
#include <memory>
#include <vector>

using json = nlohmann::json;

template <typename T>
using SPtrToVec = std::shared_ptr<std::vector<T>>;

class MainModel : public Subject
{
private:
    // User information
    std::shared_ptr<std::string> m_username = std::make_shared<std::string>("");
    std::shared_ptr<float> m_elo = std::make_shared<float>(0);
    bool m_isLoggedIn;

    SPtrToVec<std::string> m_friendList = std::make_shared<std::vector<std::string>>();
    SPtrToVec<std::string> m_friendRequestsSent = std::make_shared<std::vector<std::string>>();
    SPtrToVec<std::string> m_friendRequestsReceived = std::make_shared<std::vector<std::string>>();
    bool hasFriends;

    std::shared_ptr<std::map<int, std::vector<std::string>>> m_gameIDs = std::make_shared<std::map<int, std::vector<std::string>>>();

    std::map<std::string, SPtrToVec<Message>> m_chats;

    // Current game
    std::shared_ptr<GameModel> m_currentGame;
    bool m_isGameStarted = false;

    //    bool m_isPlayerTurn;
    //    std::unique_ptr<int> m_currentPlayer;

    // General information
    SPtrToVec<std::pair<std::string, float>> m_leaderboard = std::make_shared<std::vector<std::pair<std::string, float>>>();

    bool m_friendNotification = false, m_gameNotification = false;

public:
    template <typename P, typename V>
    auto updatePtrValue(P &ptr, V value) const noexcept -> void;
    auto updateFriendsChatMap() noexcept -> void;

    // Getters
    auto getUsername() const noexcept -> std::string *;
    auto getELO() const noexcept -> const float *;
    auto isLoggedIn() const noexcept -> bool;

    auto getFriendList() const noexcept -> const std::vector<std::string> *;
    auto getFriendRequestsSent() const noexcept -> const std::vector<std::string> *;
    auto getFriendRequestsReceived() const noexcept -> const std::vector<std::string> *;
    auto getHasFriends() const noexcept -> bool;

    auto getChatWith(const std::string &) noexcept -> SPtrToVec<Message>;

    auto getGameIDs() noexcept -> const std::map<int, std::vector<std::string>> *;

    auto isInGame() const noexcept -> bool;
    auto getCurrentGame() -> GameModel *;
    auto loadGame(const std::string &) noexcept -> void;
    auto unloadGame() -> void;
    auto createAiGame() noexcept -> void;
    auto isGameStarted() const noexcept -> bool;

    auto getLeaderboard() const noexcept -> const std::vector<std::pair<std::string, float>> *;

    auto hasFriendNotification() const noexcept -> bool;
    auto hasGameNotification() const noexcept -> bool;

    // Setters
    /**
     * Setting the username results in the player being logged in.
     * @return
     */
    auto setUsername(const std::string &) -> void;
    auto setElo(const float &) -> void;

    auto loginNotSuccessful() -> void;
    auto loginSuccessful(const std::string &) -> void;

    auto setFriendList(const std::vector<std::string> &) -> void;
    auto setHasFriends(const bool &) -> void;
    auto addFriend(const std::string &) -> void;

    auto setFriendRequestsSent(const std::vector<std::string> &) -> void;
    auto addFriendRequestSent(const std::string &) -> void;

    auto setFriendRequestsReceived(const std::vector<std::string> &) -> void;
    auto addFriendRequestReceived(const std::string &) -> void;

    auto acceptFriendRequest(const std::string &) -> void;
    auto refuseFriendRequest(const std::string &) -> void;

    auto removeFriend(const std::string &) -> void;

    auto clearFriendMessages(const std::string &) -> void;
    /**
     * @param username friend participating in the chat
     * @param message content of the message
     */
    auto addFriendMessage(const std::string &, const Message &) -> void;

    /**
     * @param username friend participating in the chat
     * @param message content of the message
     */
    //    auto addGameMessage(const std::string &, const std::vector<std::string> &, const std::string &) -> void;

    auto setLeaderboard(const std::vector<std::pair<std::string, float>> &) -> void;

    auto setGameIds(const std::map<int, std::vector<std::string>> &) -> void;
    auto addGameId(const int &, const std::vector<std::string> &) -> void;
    auto setIsGameStarted(const bool &) -> void;

    auto setFriendNotification(const bool &) -> void;
    auto setGameNotification(const bool &) -> void;

    auto processGameAction(const std::string &) -> void;
    auto playerSurrended(const std::string &username) -> void;
};
