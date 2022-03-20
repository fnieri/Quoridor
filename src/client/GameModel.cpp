//
// Created by louis on 3/19/22.
//

#include "GameModel.h"

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