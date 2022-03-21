//
// Created by louis on 3/19/22.
//

#pragma once

#include "Board.h"
#include "BoardComponent.h"
#include "src/common/Point.h"
#include "src/common/Message.h"

#include <map>
#include <memory>
#include <vector>

using json = nlohmann::json;

template <typename T>
using SPtrToVec = std::shared_ptr<std::vector<T>>;

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
    // std::vector<std::string> m_players;
    std::vector<std::shared_ptr<Player>> players;
    std::map<std::string, SPtrToVec<Message>> m_gameChats;

public:
    GameModel(int, std::vector<std::string>, std::shared_ptr<Board>);

    auto getCurrentPlayer() noexcept -> int *;

    auto isMoveValid(const Point &) const noexcept -> bool;
    auto isWallValid(const Point &) const noexcept -> bool;

    auto movePlayer(const Point &) const noexcept -> void;
    //    auto placeWall(const Wall &) const noexcept -> void;

    auto getBoardAsIntMatrix() -> std::vector<std::vector<int>>;
    auto updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix) -> void;

    auto addGameMessage(const std::string &, const Message &) -> void;

    auto hasWinner() const -> bool;
};