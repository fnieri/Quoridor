/**
 * @file GameHandler.cpp
 * @author Boris Petrov
 * @brief Handler of requests related to a game
 * @date 02/25/22
 */

#include "GameHandler.h"

#include "Database.h"
#include "EloCalculator.h"
#include "src/client/GameModel.h" // TODO: move to common
#include "src/common/SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

#include <cassert>

using json = nlohmann::json;

/**
 * GameHandler
 */

GameHandler::GameHandler(int gameID, GameHub *gameHub, UserHub *userHub, const std::vector<std::string> &players)
    : m_gameID {gameID}
    , m_gameHub {gameHub}
    , m_userHub {userHub}
    , m_gameModel {std::make_shared<GameModel>(players)}
{
}

GameHandler::GameHandler(int gameID, GameHub *gameHub, UserHub *userHub, const std::string &config)
    : m_gameID {gameID}
    , m_gameHub {gameHub}
    , m_userHub {userHub}
    , m_gameModel {std::make_shared<GameModel>(config)}
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

int GameHandler::numberOfConfirmedPlayers() const
{
    return m_confirmedPlayers;
}

void GameHandler::playerJoined(const std::string &username)
{
    // Maybe inform other players ?
    m_confirmedPlayers++;
}

void GameHandler::playerQuit(const std::string &username)
{
    // Maybe inform other players ?
    m_confirmedPlayers--;
}

bool GameHandler::areAllPlayersConfirmed() const
{
    return numberOfConfirmedPlayers() == m_gameModel->getPlayersCount();
}

bool GameHandler::areAllPlayersConnected() const
{
    bool allConnected {true};

    for (auto &player : m_gameModel->getPlayersNames())
        allConnected = allConnected && m_userHub->isConnected(player);

    return allConnected;
}

bool GameHandler::areAllPlayersNotInGame() const
{
    bool allNotInGame {true};

    for (auto &player : m_gameModel->getPlayersNames())
        allNotInGame = allNotInGame && m_userHub->isInGame(player);

    return allNotInGame;
}

void GameHandler::start()
{
    auto startRequest {SerializableMessageFactory::serializeGameStarted(getID(), m_gameModel->serialized())};

    for (auto &p : m_gameModel->getPlayersNames())
        m_userHub->relayMessageTo(p, startRequest);
}

void GameHandler::terminate()
{
    // TODO: inform players that it was terminated and use another variable
    m_isFinished = true;
}

void GameHandler::deleteFromDB()
{
    DatabaseHandler::deleteGame(getID());
}

void GameHandler::saveToDB()
{
    for (const auto &i_player : m_gameModel->getPlayersNames()) {
        std::cerr << "Saving " << i_player << std::endl;
        DatabaseHandler::addGameIdToUser(i_player, getID());
    }

    DatabaseHandler::setGameBoardConfig(getID(), m_gameModel->serialized());
}

void GameHandler::updateELO(const std::string &winner)
{
    std::vector<float> currentELOs;
    std::vector<bool> winningState;

    for (auto &i_player : m_gameModel->getPlayersNames()) {
        currentELOs.push_back(DatabaseHandler::getELO(i_player));
        winningState.push_back(i_player == winner);
    }

    EloCalculator eloCalc {currentELOs, winningState};
    eloCalc.calculateELO();
    auto finalELOs {eloCalc.getFinalELOs()};

    for (auto i {0}; i < m_gameModel->getPlayersNames().size(); ++i) {
        DatabaseHandler::setELO(m_gameModel->getPlayersNames().at(i), finalELOs.at(i));
    }
}

void GameHandler::processRequest(const std::string &serRequest)
{
    auto request(json::parse(serRequest));

    if (request["action"] == toJsonString(GameAction::SURRENDER)) {
        m_gameModel->playerSurrendered(request["sender"]);
        if (m_gameModel->hasWinner()) {
            updateELO(m_gameModel->getWinner());
            m_isFinished = true;
        }

    } else if (request["action"] == toJsonString(GameAction::PROPOSE_SAVE)) {
        m_saveAcceptance++;

    } else if (request["action"] == toJsonString(GameAction::ACCEPT_SAVE)) {
        m_saveAcceptance++;

    } else if (request["action"] == toJsonString(GameAction::REFUSE_SAVE)) {
        m_saveAcceptance--;

    } else if (request["action"] == toJsonString(GameAction::END_GAME)) {
        updateELO(request["winner"]);
        m_isFinished = true;
    }

    for (auto &p : m_gameModel->getPlayersNames())
        if (p != request["sender"])
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

    while (DatabaseHandler::isGameIdUsed(ID)) {
        ID = std::rand();
    }

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
    auto request = json::parse(serRequest);
    std::cout << request << std::endl;

    auto gameID {getUniqueID()};

    std::vector<std::string> gPlayers;
    for (auto &i_user : request["receivers"]) {
        gPlayers.push_back(i_user.get<std::string>());
    }

    DatabaseHandler::createGame(gameID, gPlayers, (int)gPlayers.size(), request["game_configuration"]);

    auto config {request["game_configuration"].dump()};
    auto tmp {std::make_shared<GameHandler>(gameID, this, m_userHub, config)};

    tmp->saveToDB();
    m_games.push_back(tmp);

    for (auto &i_user : request["receivers"]) {
        m_userHub->relayMessageTo(i_user, serRequest);
    }
}

void GameHub::createGameFromDB(int gameID)
{
    auto config {DatabaseHandler::getGameConfig(gameID).dump()};
    auto tmp {std::make_shared<GameHandler>(gameID, this, m_userHub, config)};

    m_games.push_back(tmp);
}

void GameHub::processGameJoin(const std::string &serRequest)
{
    auto request(json::parse(serRequest));
    auto targetGame {getGame(request["game_id"])};

    if (!targetGame) {
        createGameFromDB(request["game_id"]);
        targetGame = getGame(request["game_id"]);
    }

    targetGame->playerJoined(request["username"]);

    if (targetGame->areAllPlayersConfirmed() && targetGame->areAllPlayersConnected() && targetGame->areAllPlayersNotInGame()) {
        targetGame->start();
    }
}

void GameHub::processGameQuit(const std::string &serRequest)
{
    auto request(json::parse(serRequest));
    auto targetGame {getGame(request["game_id"])};

    targetGame->playerQuit(request["username"]);

    if (targetGame->numberOfConfirmedPlayers() == 0) {
        unloadGame(request["game_id"]);
    }
}

void GameHub::unloadGame(int gameID)
{
    auto targetGame {getGame(gameID)};

    if (targetGame) {
        targetGame->terminate();
        eraseFinished();
    }
}

void GameHub::processRequest(const std::string &serRequest)
{
    // Mutex when operating on game creation
    std::lock_guard<std::mutex> guard {m_gamesMutex};

    auto request = json::parse(serRequest);

    if (request["action"] == toJsonString(GameSetup::CREATE_GAME)) {
        processGameCreation(serRequest);
    } else if (request["action"] == toJsonString(GameSetup::JOIN_GAME)) {
        processGameJoin(serRequest);

    } else if (request["action"] == toJsonString(GameSetup::QUIT_GAME)) {
        processGameQuit(serRequest);
    }
}
