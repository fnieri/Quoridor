#pragma once

#include "src/client/Board.h"
#include "src/client/Corridor.h"
#include "src/common/Message.h"
#include "src/common/MessageEnums/DataTypes.h"
#include "src/common/MessageEnums/Domain.h"
#include "src/common/Observer.h"
#include "Board.h"
#include "BoardComponent.h"
#include "Cell.h"
#include "Corridor.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerEnum.h"
#include "ServerBridge.h"
//#include "MainController.h"
#include "WallAction.h"
#include "WallEnum.h"
#include "src/common/Observer.h"
#include "src/common/Point.h"
#include "src/common/SerializableMessageFactory.h"


#include <map>
#include <memory>
#include <vector>

using json = nlohmann::json;

template <typename T>
using SPtrToVec = std::shared_ptr<std::vector<T>>;
//using SPtrToVec2 = std::make_shared<std::vector<T>()>;

class GameModel;

class MainModel : public Subject
{
private:
    // User information
    std::shared_ptr<std::string> m_username;
    std::shared_ptr<float> m_elo;
    bool m_isLoggedIn;

    SPtrToVec<std::string> m_friendList = std::make_shared<std::vector<std::string>>();
    SPtrToVec<std::string> m_friendRequestsSent = std::make_shared<std::vector<std::string>>();
    SPtrToVec<std::string> m_friendRequestsReceived  = std::make_shared<std::vector<std::string>>();

    SPtrToVec<int> m_gameIDs;

    std::map<std::string, SPtrToVec<Message>> m_chats;

    // Current game
    std::shared_ptr<Board> m_currentGame;

    bool m_isPlayerTurn;
    std::unique_ptr<int> m_currentPlayer;

    // General information
    SPtrToVec<std::pair<std::string, float>> m_leaderboard;

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

    auto getChatWith(const std::string &) const noexcept -> const SPtrToVec<Message>;

    auto getGameIDs() const noexcept -> const std::vector<int> *;

    auto isInGame() const noexcept -> bool;
    //    auto getCurrentGame() const noexcept -> const GameModel*;
    auto isPlayerTurn() const noexcept -> bool;

    auto getLeaderboard() const noexcept -> const std::vector<std::pair<std::string, float>> *;

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
    auto addFriend(const std::string &) -> void;

    auto setFriendRequestsSent(const std::vector<std::string> &) -> void;
    auto addFriendRequestSent(const std::string &) -> void;

    auto setFriendRequestsReceived(const std::vector<std::string> &) -> void;
    auto addFriendRequestReceived(const std::string &) -> void;

    auto refuseFriendRequest(const std::string &) -> void;

    auto removeFriend(const std::string &) -> void;

    /**
     * @param username friend participating in the chat
     * @param message content of the message
     */
    auto addFriendMessage(const std::string &, const std::string &) -> void;

    /**
     * @param username friend participating in the chat
     * @param message content of the message
     */
    //    auto addGameMessage(const std::string &, const std::vector<std::string> &, const std::string &) -> void;

    auto setLeaderboard(const std::vector<std::pair<std::string, float>> &) -> void;

    auto setGameIds(const std::vector<int> &) -> void;

//    auto loadGame
};

/**
 * @param gameID the identifier of the game
 * @param players players in the game
 * @param boardConfiguration initial positions of walls and players
 */
class GameModel
{
private:
    std::shared_ptr<Board> m_board;
    int m_gameId;
    int currentPlayerIdx {0};
    std::vector<std::string> m_players;
    std::vector<std::shared_ptr<Player>> players;

public:
    GameModel(int, std::vector<std::string>, std::shared_ptr<Board>);

    auto getCurrentPlayer() noexcept -> int *;

    auto isMoveValid(const Point &) const noexcept -> bool;
    auto isWallValid(const Point &) const noexcept -> bool;

    auto movePlayer(const Point &) const noexcept -> void;
    //    auto placeWall(const Wall &) const noexcept -> void;

    auto getBoardAsIntMatrix() -> std::vector<std::vector<int>>;
    auto updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix) -> void;
};