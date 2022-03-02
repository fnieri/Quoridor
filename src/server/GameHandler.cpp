/**
 * @file GameHandler.cpp
 * @author Boris Petrov
 * @brief Handler of requests related to a game
 * @date 02/25/22
 */

#include "GameHandler.h"

#include "Database.h"
#include "EloCalculator.h"
#include "src/common/SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

#include <cassert>

using json = nlohmann::json;

GameHandler::GameHandler(int gameID, GameHub *gameHub, UserHub *userHub)
    : m_gameID {gameID}
    , m_gameHub {gameHub}
    , m_userHub {userHub}
{
}

bool GameHandler::isFinished() const
{
    return m_isFinished;
}

int GameHandler::getID() const noexcept
{
    return m_gameID;
}

void GameHandler::setConfiguration(const std::string &configuration)
{
    m_configuration = configuration;
}

void GameHandler::addPlayer(const std::string &username)
{
    m_players.push_back(username);

    assert(m_players.size() <= 4);
}

int GameHandler::numberOfConfirmedPlayers() const
{
    int confirmedPlayers;

    for (auto &state : m_confirmedPlayers)
        confirmedPlayers += static_cast<int>(state);

    return confirmedPlayers;
}

void GameHandler::setConfirmationState(const std::string &username, bool state)
{
    for (auto i {0}; i < m_players.size(); ++i) {
        if (m_players[i] == username) {
            m_confirmedPlayers[i] = state;
            break;
        }
    }
}

void GameHandler::confirmPlayer(const std::string &username)
{
    setConfirmationState(username, true);
}

void GameHandler::cancelPlayer(const std::string &username)
{
    setConfirmationState(username, false);
}

bool GameHandler::areAllPlayersConfirmed() const
{
    return numberOfConfirmedPlayers() == m_players.size();
}

bool GameHandler::areAllPlayersConnected() const
{
    bool allConnected {true};

    for (auto &player : m_players)
        allConnected = allConnected && m_userHub->isConnected(player);

    return allConnected;
}

bool GameHandler::areAllPlayersNotInGame() const
{
    bool allNotInGame {true};

    for (auto &player : m_players)
        allNotInGame = allNotInGame && m_userHub->isInGame(player);

    return allNotInGame;
}

void GameHandler::start()
{
    // TODO wait for serialized request
    /* auto startRequest {SerializableMessageFactory::getGameStarted(m_configuration)}; */

    /* for (auto &p : m_players) */
    /*     m_userHub->relayMessageTo(p, startRequest); */
}

void GameHandler::terminate()
{
}

void GameHandler::deleteFromDB()
{
    /* DatabaseHandler::deleteGame(getID()); */
}

void GameHandler::saveToDB()
{
    /* DatabaseHandler::saveGame(getID(), m_players, m_players.size(), json::parse(m_configuration)); */
}

void GameHandler::updateELO(const std::string &winner)
{
    std::vector<float> currentELOs;
    std::vector<bool> winningState;

    for (auto &i_player : m_players) {
        currentELOs.push_back(DatabaseHandler::getELO(i_player));
        winningState.push_back(i_player == winner);
    }

    EloCalculator eloCalc {currentELOs, winningState};
    eloCalc.calculateELO();
    auto finalELOs {eloCalc.getFinalELOs()};

    for (auto i {0}; i < m_players.size(); ++i) {
        DatabaseHandler::setELO(m_players.at(i), finalELOs.at(i));
    }
}

void GameHandler::processRequest(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    // TODO: handle
    // - endgame

    for (auto &p : m_players)
        if (p != request["username"])
            m_userHub->relayMessageTo(p, serRequest);
}

/**
 * GameHub
 */

GameHub::GameHub(UserHub *userHub)
    : m_userHub {userHub}
{
}

int GameHub::getUniqueID() const
{
    auto ID {std::rand()};

    // TODO see with database
    /* while (DatabaseHandler::isGameIdUsed(ID)) { */
    /*     ID = std::rand(); */
    /* } */

    return ID;
}

std::shared_ptr<GameHandler> GameHub::getGame(int gameID) const
{
    std::shared_ptr<GameHandler> gameHandle;

    auto gameHandleIt {std::find_if(m_games.begin(), m_games.end(), [gameID](const auto &g) { return g->getID() == gameID; })};

    if (gameHandleIt != m_games.end())
        gameHandle = *gameHandleIt;

    return gameHandle;
}

void GameHub::eraseFinished()
{
    m_games.erase(std::remove_if(m_games.begin(), m_games.end(), [](auto &g) { return g->isFinished(); }), m_games.end());
}

void GameHub::processGameCreation(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    auto gameID {getUniqueID()};
    auto tmp {std::make_shared<GameHandler>(gameID, this, m_userHub)};

    tmp->addPlayer(request["username_sending"]);
    tmp->confirmPlayer(request["username_sending"]);

    for (auto &i_user : request["username_receiving"])
        tmp->addPlayer(i_user);

    tmp->setConfiguration(request["game_configuration"]);

    for (auto &i_user : request["username_receiving"]) {
        m_userHub->relayMessageTo(i_user, serRequest);
    }

    m_games.push_back(tmp);
}

void GameHub::processGameJoin(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};
    auto targetGame {getGame(request["game_id"])};

    targetGame->confirmPlayer(request["username"]);

    if (targetGame->areAllPlayersConfirmed() && targetGame->areAllPlayersConnected() && targetGame->areAllPlayersNotInGame()) {
        targetGame->start();
    }
}

void GameHub::processGameQuit(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};
    auto targetGame {getGame(request["game_id"])};

    targetGame->confirmPlayer(request["username"]);

    if (targetGame->numberOfConfirmedPlayers() == 0) {
        targetGame->terminate();
        eraseFinished();
    }
}

void GameHub::removeGame(int gameID)
{
    auto targetGame {getGame(gameID)};

    if (targetGame) {
        targetGame->deleteFromDB();
        targetGame->terminate();
    }
}

void GameHub::processRequest(const std::string &serRequest)
{
    // Mutex when operating on game creation
    std::lock_guard<std::mutex> guard {m_gamesMutex};

    auto request {json::parse(serRequest)};

    // TODO see with serialized req
    /* if (request["action"] == toJsonString(GameSetup::GAME_CREATE)) { */
    /*     processGameCreation(serRequest); */

    /* } else if (request["action"] == toJsonString(GameSetup::GAME_JOIN)) { */
    /*     processGameJoin(serRequest); */

    /* } else if (request["action"] == toJsonString(GameSetup::GAME_QUIT)) { */
    /*     processGameInvitationQuit(serRequest); */
    /* } */
}
