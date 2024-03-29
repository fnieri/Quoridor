/**
 * @file GameModel.cpp
 * @author Louis Vanstappen
 * @author Boris Petrov
 * @brief Game Model
 * @date 02/25/22
 */

#pragma once

#include "Board.h"
#include "BoardComponent.h"
#include "src/common/Message.h"
#include "src/common/Point.h"
#include "src/common/aiPlayer.h"

#include <nlohmann/json_fwd.hpp>

#include <map>
#include <memory>
#include <vector>

using json = nlohmann::json;

template <typename T>
using SPtrToVec = std::shared_ptr<std::vector<T>>;

class WallAction;
class PlayerAction;

/**
 * @param gameID the identifier of the game
 * @param players players in the game
 * @param boardConfiguration initial positions of walls and players
 */
class GameModel
{
private:
    int m_gameId {-1};

    std::string m_winner {""};

    auto addPlayer(PawnColors, const Point &, int, FinishLine, const std::string &) -> void;

    auto getPlayerFromColorId(const int &id) -> std::shared_ptr<Player>;
    auto getWallActionFromSer(const std::string &) -> WallAction;
    auto getPlayerActionFromSer(const std::string &) -> PlayerAction;

    /* std::map<std::string, SPtrToVec<Message>> m_gameChats; */

protected:
    std::shared_ptr<Board> m_board = std::make_shared<Board>();

    std::vector<std::shared_ptr<Player>> m_players{};

    int m_currentPlayerIdx {0};

public:
    /**
     * @brief New game, with default config
     * @param players vector of their usernames
     */
    GameModel(const std::vector<std::string> &);
    /**
     * @brief Existing game, from an existent conf
     * @param players vector of their usernames
     */
    GameModel(const std::string &);

    /**
     * @note Winner can be established.
     */
    virtual auto processAction(const std::string &) -> void;

    auto getCurrentPlayer() noexcept -> const int *;

    auto isMoveValid(const Point &, const int &playerPerspective = 0) const noexcept -> bool;
    auto isWallValid(const Point &, WallOrientation, const int &playerPerspective = 0) const noexcept -> bool;

    auto getPlayerAction(const Point &, const int &playerPerspective = 0) const noexcept -> PlayerAction;
    auto getWallAction(const Point &, WallOrientation, const int &playerPerspective = 0) const noexcept -> WallAction;

    auto getPlayerIdx(const std::string &) const noexcept -> int;
    auto getPlayersRemainingWalls() noexcept -> std::map<std::string, int>;

    auto hasWinner() const -> bool;
    auto getWinner() const -> std::string;

    auto getPlayersNames() const -> std::vector<std::string>;
    auto getPlayersCount() const -> int;

    /**
     * @note Winner can be established.
     */
    auto playerSurrended(const std::string &) -> void;

    auto rotatedBoard(FinishLine fl) -> std::vector<std::vector<std::shared_ptr<BoardComponent>>>;
    auto debugPrintBoard() -> void;

    auto serialized() -> nlohmann::json;

    /* auto getBoardAsIntMatrix() -> std::vector<std::vector<int>>; */
    auto updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix, int playerIdx) -> void;
    /* auto addGameMessage(const std::string &, const Message &) -> void; */
};

class AiGameModel : public GameModel
{
    aiPlayer m_aiPlayer {};

public:
    AiGameModel(const std::vector<std::string> &);
    auto processAction(const std::string &) -> void override;
};
