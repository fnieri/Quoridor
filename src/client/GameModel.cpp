/**
 * @file GameModel.h
 * @author Louis Vanstappen
 * @author Boris Petrov
 * @brief Game Model
 * @date 02/25/22
 */

#include "GameModel.h"

#include "src/client/PlayerAction.h"
#include "src/client/WallAction.h"

#include <iostream>

GameModel::GameModel(const std::vector<std::string> &p_players)
{
    const std::array<Point, 4> defaultPos {Point {4, 0}, Point {4, 8}, Point {0, 4}, Point {8, 4}};

    for (int i = 0; i < p_players.size(); ++i) {

        auto color {static_cast<PawnColors>(i)};
        auto pos {defaultPos[i]};
        auto remWalls {10};
        auto finishLine {static_cast<FinishLine>(i)};
        auto username {p_players[i]};

        addPlayer(color, pos, remWalls, finishLine, username);
    }
}

GameModel::GameModel(const std::string &p_conf)
{
    auto conf(json::parse(p_conf));

    for (auto &i_plr : conf["players"]) {

        auto color {static_cast<PawnColors>(i_plr["player_id"])};
        auto pos {Point::deserialized(i_plr["player_position"].dump())};
        auto remWalls {static_cast<int>(i_plr["remaining_walls"])};
        auto finishLine {static_cast<FinishLine>(i_plr["finish_line"])};
        auto username {static_cast<std::string>(i_plr["username"])};

        addPlayer(color, pos, remWalls, finishLine, username);
    }
}

auto GameModel::addPlayer(PawnColors color, const Point &pos, int remWalls, FinishLine finishLine, const std::string &username) -> void
{
    m_players.push_back(std::make_shared<Player>(color, pos, remWalls, finishLine, username));
    m_board->spawnPlayer(m_players.back());
}

auto GameModel::getWallActionFromSer(const std::string &ser) -> WallAction
{
    auto deser(json::parse(ser));

    auto player {m_players[deser["player_id"]]};
    auto destCell {Point::deserialized(deser["wall_cell"].dump())};
    auto wallOri {static_cast<WallOrientation>(deser["wall_orientation"])};

    return WallAction {m_board, player, destCell, wallOri};
}

auto GameModel::getPlayerActionFromSer(const std::string &ser) -> PlayerAction
{
    auto deser(json::parse(ser));

    auto player {m_players[deser["player_id"]]};
    auto endPos {Point::deserialized(deser["end_position"].dump())};

    // The division by two is neccessary due to ctor of PlayerAction.
    // It multiplies it by 2 O_O
    return PlayerAction {m_board, player, endPos / 2};
}

auto GameModel::processAction(const std::string &p_action) -> void
{
    auto action(json::parse(p_action));

    if (action["action_type"] == "wall") {
        auto specAction {getWallActionFromSer(action.dump())};

        assert(specAction.isWallPlacementLegal() && specAction.isWallPlacementValid());
        specAction.executeAction();

    } else if (action["action_type"] == "player") {
        auto specAction {getPlayerActionFromSer(action.dump())};

        assert(specAction.isActionValid());
        specAction.executeAction();

        if (specAction.isGameOver()) {
            m_winner = m_players.at(m_currentPlayerIdx)->getUsername();
        }
    }

    // Next turn
    m_currentPlayerIdx = ++m_currentPlayerIdx % m_players.size();
}

auto GameModel::getCurrentPlayer() noexcept -> const int *
{
    return &m_currentPlayerIdx;
}

/* auto GameModel::isMoveValid(const Point &movePoint) const noexcept -> bool */
/* { */
/*     PlayerAction action {m_board, m_players.at(m_currentPlayerIdx), movePoint/2}; */
/*     return action.isActionValid(); */
/* } */

/* auto GameModel::isWallValid(const Point &dest, WallOrientation ori) const noexcept -> bool */
/* { */
/*     WallAction action {m_board, m_players.at(m_currentPlayerIdx), dest, ori}; */
/*     return action.isWallPlacementLegal() && action.isWallPlacementValid(); */
/* } */

auto GameModel::getPlayerAction(const Point &dest) const noexcept -> PlayerAction
{
    return PlayerAction {m_board, m_players.at(m_currentPlayerIdx), dest / 2};
}

auto GameModel::getWallAction(const Point &dest, WallOrientation orientation) const noexcept -> WallAction
{
    return WallAction {m_board, m_players.at(m_currentPlayerIdx), dest, orientation};
}

auto GameModel::hasWinner() const -> bool
{
    return m_winner.empty();
}

auto GameModel::getWinner() const -> std::string
{
    return m_winner;
}

auto GameModel::playerSurrendered(const std::string &p_username) -> void
{
    auto playerIt {std::find_if(m_players.begin(), m_players.end(), [p_username](auto &p) { return p->getUsername() == p_username; })};

    if (playerIt == m_players.end()) {
        std::cerr << "The players doesn't exist!\n";
        return;
    }

    auto player {*playerIt};

    m_board->removePlayer(player);
    m_players.erase(playerIt);

    if (m_players.size() == 1) {
        m_winner = m_players.front()->getUsername();
    }
}

/* auto GameModel::addGameMessage(const std::string &, const Message &) -> void */
/* { */
/* } */
