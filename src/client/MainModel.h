#include "src/common/Observer.h"
#include "src/client/Board.h"

#include <memory>
#include <vector>
#include <map>

template <typename T>
using SPtrToVec = std::shared_ptr<std::vector<T>>;

class GameModel;

class MainModel : public Subject
{
private:
    // User information
    std::shared_ptr<std::string> m_username;
    std::shared_ptr<float> m_elo;
    bool m_isLoggedIn;

    SPtrToVec<std::string> m_friendList;
    SPtrToVec<std::string> m_friendRequestsSent;
    SPtrToVec<std::string> m_friendRequestsReceived;

    SPtrToVec<int> m_gameIDs;

    std::map<std::string, SPtrToVec<std::string>> m_chats;

    // Current game
    std::shared_ptr<Board> m_currentGame;

    bool m_isPlayerTurn;
    std::unique_ptr<int> m_currentPlayer;


    // General information
    SPtrToVec<std::pair<std::string, float>> m_leaderboard;

public:
    MainModel();

    // Getters
    auto getUsername() const noexcept -> const *std::string;
    auto getELO() const noexcept -> const *float;
    auto isLoggedIn() const noexcept -> bool;

    auto getFriendList() const noexcept -> const *std::vector<std::string>>;
    auto getFriendRequestsSent() const noexcept -> const *std::vector<std::string>;
    auto getFriendRequestsReceived() const noexcept -> const *std::vector<std::string>;

    auto getChatWith(const std::string &) const noexcept -> const *std::vector<std::string>;

    auto getGameIDs() const noexcept -> const *std::vector<int>;

    auto isInGame() const noexcept -> bool;
    auto getCurrentGame() const noexcept -> const *GameModel;

    auto getLeaderboard() const noexcept -> const *std::vector<std::pair<std::string, float>>;

    // Setters
    /**
     * Setting the username results in the player being logged in.
     * @return
     */
    auto setUsername(const std::string &) -> void;
    auto setELO(const int &) -> void;

    auto loginNotSuccessful() -> void;
    auto loginSuccessful(const std::string &) -> void;

    auto setFriendList(const std::vector<std::string> &) -> void;
    auto addFriend(const std::string &);

    auto setFriendRequestsSent(const std::vector<std::string> &) -> void;
    auto addFriendRequestSent(const std::string &) -> void;

    auto setFriendRequestsReceived(const std::vector<std::string> &) -> void;
    auto addFriendRequestReceived(const std::string &) -> void;

    /**
     * @param username friend participating in the chat
     * @param message content of the message
     */
    auto addMessageToChat(const std::string &, const std::string &);
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

public:
    GameModel(int, std::vector<std::string>, );

    auto getCurrentPlayer() const noexcept -> *int;

    auto isMoveValid(const Point &) const noexcept -> bool;
    auto isWallValid(const Point &) const noexcept -> bool;

    auto movePlayer(const Point &) const noexcept -> void;
    auto placeWall(const Wall &) const noexcept -> void;

    auto getBoardAsIntMatrix() -> std::vector<std::vector<int>>;
    auto updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix) -> void;
};