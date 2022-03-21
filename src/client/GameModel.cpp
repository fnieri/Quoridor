//
// Created by louis on 3/19/22.
//

#include "GameModel.h"

//GameModel::GameModel(int gameId, std::vector<std::string> players, std::shared_ptr<Board> board)
//    : m_gameId(gameId)
//    , m_players(std::move(players))
//    , m_board(std::move(board))
//{
//}
//
//GameModel::GameModel(const std::string &p_conf)
//{
//    auto conf(json::parse(p_conf));
//
//    for (auto &i_plr : conf["players"]) {
//
//        auto color {static_cast<PawnColors>(i_plr["player_id"])};
//        auto pos {Point::deserialized(i_plr["player_position"].dump())};
//        auto remWalls {static_cast<int>(i_plr["remaining_walls"])};
//        auto finishLine {static_cast<FinishLine>(i_plr["finish_line"])};
//        auto username {static_cast<std::string>(i_plr["username"])};
//
//        m_players.push_back(std::make_shared<Player>(color, pos, remWalls, finishLine, username));
//        m_board->spawnPlayer(m_players.back());
//    }
//}
//
//auto GameModel::getCurrentPlayer() noexcept -> int *
//{
//    return &currentPlayerIdx;
//}
//
//auto GameModel::isMoveValid(const Point &movePoint) const noexcept -> bool
//{
//    //    PlayerAction move {board, players.at(currentPlayerIndex), movePoint/2};
//    //    return move.isActionValid();
//}
//
//auto GameModel::addGameMessage(const std::string &, const Message &) -> void
//{
//}
