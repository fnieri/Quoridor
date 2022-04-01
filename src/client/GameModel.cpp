/**
 * @file GameModel.h
 * @author Louis Vanstappen
 * @author Boris Petrov
 * @brief Game Model
 * @date 02/25/22
 */

#include "GameModel.h"

#include "Cell.h"
#include "Corridor.h"
#include "src/client/PlayerAction.h"
#include "src/client/WallAction.h"

#include <nlohmann/json.hpp>

#include <cassert>
#include <iostream>

using json = nlohmann::json;

GameModel::GameModel(const std::vector<std::string> &p_players)
{
    assert(p_players.size() == 2 || p_players.size() == 4);

    const std::array<Point, 4> defaultPos {Point {4, 8}, Point {4, 0}, Point {0, 4}, Point {8, 4}};

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

        auto color {static_cast<PawnColors>(i_plr["id"])};
        auto pos {Point::deserialized(i_plr["position"].dump())};
        auto remWalls {static_cast<int>(i_plr["remaining_walls"])};
        auto finishLine {static_cast<FinishLine>(i_plr["finish_line"])};
        auto username {static_cast<std::string>(i_plr["username"])};

        addPlayer(color, pos, remWalls, finishLine, username);
    }

    m_board->putSerializedWalls(conf["walls"]);
    m_currentPlayerIdx = conf["current_player_id"];
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
    auto wallOri {deser["wall_orientation"] == toJsonOutput(WallOrientation::Horizontal) ? WallOrientation::Horizontal : WallOrientation::Vertical};

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
    auto action = json::parse(p_action);

    /* std::cerr << "Before action\n"; */

    if (action["action_type"] == "wall") {
        auto specAction {getWallActionFromSer(action.dump())};

        assert(specAction.isWallPlacementLegal() && specAction.isWallPlacementValid());

        /* std::cerr << "Before exec action\n"; */
        specAction.executeAction();
        /* std::cerr << "After exec action\n"; */

    } else if (action["action_type"] == "player") {
        auto specAction {getPlayerActionFromSer(action.dump())};

        assert(specAction.isActionValid());
        specAction.executeAction();

        if (specAction.isGameOver()) {
            m_winner = m_players.at(m_currentPlayerIdx)->getUsername();
        }
    }

    /* std::cerr << "After action\n"; */

    // Next turn
    m_currentPlayerIdx = ++m_currentPlayerIdx % m_players.size();
}

auto GameModel::getCurrentPlayer() noexcept -> const int *
{
    return &m_currentPlayerIdx;
}

auto GameModel::isMoveValid(const Point &movePoint, const int &playerPerspective) const noexcept -> bool
{
    auto action = getPlayerAction(movePoint, playerPerspective);
    return action.isActionValid();
}

auto GameModel::isWallValid(const Point &dest, WallOrientation ori, const int &playerPerspective) const noexcept -> bool
{
    auto action = getWallAction(dest, ori, playerPerspective);
    return action.isWallPlacementLegal() && action.isWallPlacementValid();
}

auto GameModel::getPlayerAction(const Point &dest, const int &playerPerspective) const noexcept -> PlayerAction
{
    auto fl = m_players.at(playerPerspective)->getFinishLine();
    auto rotMov = m_board->getRotatedMatrixPosition(dest * 2, fl, true) / 2;

    return PlayerAction {m_board, m_players.at(m_currentPlayerIdx), rotMov};
}

auto GameModel::getWallAction(const Point &dest, WallOrientation orientation, const int &playerPerspective) const noexcept -> WallAction
{
    auto fl = m_players.at(playerPerspective)->getFinishLine();

    auto actualPos = dest;
    auto actualOri = orientation;

    if (fl == FinishLine::South) {
        actualPos = actualPos + Point {1, 1};

    } else if (fl == FinishLine::East) {
        actualPos = actualPos + Point {0, 1};
        actualOri = orientation == WallOrientation::Horizontal ? WallOrientation::Vertical : WallOrientation::Horizontal;

    } else if (fl == FinishLine::West) {
        actualPos = actualPos + Point {1, 0};
        actualOri = orientation == WallOrientation::Horizontal ? WallOrientation::Vertical : WallOrientation::Horizontal;
    }

    auto rotMov = m_board->getRotatedMatrixPosition(actualPos * 2, fl, true) / 2;

    return WallAction {m_board, m_players.at(m_currentPlayerIdx), rotMov, actualOri};
}

auto GameModel::hasWinner() const -> bool
{
    return !m_winner.empty();
}

auto GameModel::getWinner() const -> std::string
{
    return m_winner;
}

auto GameModel::getPlayersNames() const -> std::vector<std::string>
{
    auto playersNames {std::vector<std::string> {}};

    for (auto &i_player : m_players)
        playersNames.emplace_back(i_player->getUsername());

    return playersNames;
}

auto GameModel::getPlayersCount() const -> int
{
    return m_players.size();
}

auto GameModel::playerSurrended(const std::string &p_username) -> void
{
    auto playerIt {std::find_if(m_players.begin(), m_players.end(), [p_username](auto &p) { return p->getUsername() == p_username; })};

    if (playerIt == m_players.end()) {
        std::cerr << "The player doesn't exist!\n";
        return;
    }

    auto player {*playerIt};

    m_board->removePlayer(player);
    m_players.erase(playerIt);

    if (m_players.size() == 1) {
        m_winner = m_players.front()->getUsername();
    }
}

auto GameModel::updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix, int playerIdx) -> void
{
    const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
              occupiedHorizontalQuoridor = 7;
    boardIntMatrix.clear();
    if (m_players.empty() || hasWinner())
        return;

    auto finishLine = m_players.at(playerIdx)->getFinishLine();

    std::vector<std::vector<std::shared_ptr<BoardComponent>>> boardMatrix = rotatedBoard(finishLine);

    for (int y = 0; y < boardMatrix.size(); y++) {
        std::vector<int> row;
        for (int x = 0; x < boardMatrix.at(y).size(); x++) {

            // Pawns
            if (m_board->isCell(m_board->getRotatedMatrixPosition({x, y}, finishLine, true))) {
                if (m_board->isFree(m_board->getRotatedMatrixPosition({x, y}, finishLine, true)))
                    row.push_back(freeCell);
                else {
                    auto playerCell = (std::dynamic_pointer_cast<Cell>(boardMatrix.at(x).at(y)));
                    switch (playerCell->getPlayer()->getColor()) {
                    case PawnColors::Yellow:
                        row.push_back(playerOne);
                        break;
                    case PawnColors::Green:
                        row.push_back(playerTwo);
                        break;
                    case PawnColors::Blue:
                        row.push_back(playerThree);
                        break;
                    case PawnColors::Purple:
                        row.push_back(playerFour);
                        break;
                    }
                }
            }

            // Corridors
            else if (boardMatrix.at(x).at(y) && boardMatrix.at(x).at(y)->isOccupied()) {
                auto orientation = std::dynamic_pointer_cast<Corridor>(boardMatrix.at(x).at(y))->getOrientation();

                switch (finishLine) {
                case FinishLine::West:
                case FinishLine::East:
                    orientation = orientation == WallOrientation::Vertical ? WallOrientation::Horizontal : WallOrientation::Vertical;
                    break;
                }

                row.push_back((orientation == WallOrientation::Vertical ? occupiedVerticalQuoridor : occupiedHorizontalQuoridor));
            } else
                row.push_back(emptyQuoridor);
        }
        boardIntMatrix.push_back(row);
    }

//    std::cerr << "updateBoardIntMatrix: after construction\n";
}

auto GameModel::rotatedBoard(FinishLine fl) -> std::vector<std::vector<std::shared_ptr<BoardComponent>>>
{
    return m_board->getRotatedBoardMatrix(fl);
}

/* auto GameModel::rotatedPosition(const Point &pos, FinishLine fl) -> Point */
/* { */
/*     auto matPos = pos * 2; */
/*     auto rotatedMatPos = m_board->getRotatedMatrixPosition(matPos, fl, false); */

/*     return rotatedPosition / 2; */
/* } */

auto GameModel::debugPrintBoard() -> void
{
    m_board->debugPrint();
}

auto GameModel::serialized() -> json
{
    auto playerPos(json::array());
    auto wallPos(m_board->getSerializedWalls());

    for (auto &i_player : m_players) {

        auto playerID {static_cast<int>(i_player->getColor())};
        auto finiLine {static_cast<int>(i_player->getFinishLine())};
        auto username {i_player->getUsername()};
        auto position {i_player->getPosition()};
        auto remWalls {i_player->nWalls()};

        playerPos.push_back({
            {"id", playerID},
            {"finish_line", finiLine},
            {"username", username},
            {"position", position.serialized()},
            {"remaining_walls", remWalls},
        });
    }

    auto serGame(json {
        {"current_player_id", m_currentPlayerIdx},
        {"walls", wallPos},
        {"players", playerPos},
    });

    return serGame;
}

auto GameModel::getPlayerIdx(const std::string &username) const noexcept -> int
{
    for (auto &i_player : m_players) {
        if (i_player->getUsername() == username)
            return i_player->getIndex();
    }
    return -2;
}

auto GameModel::getPlayersRemainingWalls() noexcept -> std::map<std::string, int>
{
    std::map<std::string, int> remainingWalls;
    for (auto &i_player : m_players) {
        remainingWalls[i_player->getUsername()] = i_player->nWalls();
    }
    return remainingWalls;
}

/* auto GameModel::addGameMessage(const std::string &, const Message &) -> void */
/* { */
/* } */
AiGameModel::AiGameModel(const std::vector<std::string> &p_players)
    : GameModel(p_players)
{
}

auto AiGameModel::processAction(const std::string &p_action) -> void
{
    GameModel::processAction(p_action);

    // ai plays
    auto aiPlay = m_aiPlayer.findAction(m_board, m_players.at((m_currentPlayerIdx) % m_players.size()), m_players.at(m_currentPlayerIdx));
    auto aiPlayJsonStr = aiPlay.serialized().dump();
    GameModel::processAction(aiPlayJsonStr);
}
