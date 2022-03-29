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
    std::cout << "GameHandler::setConfiguration: " << configuration << std::endl;
    m_configuration = configuration;

    auto config = json::parse(configuration);
    auto players = config.at("players");
    m_players.clear();
    for (auto &player : players) {
        addPlayer(player.get<std::string>()); // Add player by its username
    }
    m_confirmedPlayers.fill(false);
}

void GameHandler::addPlayer(const std::string &username)
{
    m_players.push_back(username);

    assert(m_players.size() <= 4);
}

int GameHandler::numberOfConfirmedPlayers() const
{
    int confirmedPlayers = 0;

    for (auto &state : m_confirmedPlayers)
        confirmedPlayers += static_cast<int>(state);

    return confirmedPlayers;
}

void GameHandler::setConfirmationState(const std::string &username, bool state)
{
    for (auto i {0}; i < m_players.size(); ++i) {
        if (m_players[i] == username) {
            std::cout << "GameHandler::setConfirmationState: " << m_players[i] << " == " << username << " ? " << std::endl;
            m_confirmedPlayers[i] = state;
            break;
        }
    }
}

void GameHandler::playerJoined(const std::string &username)
{
    setConfirmationState(username, true);
}

void GameHandler::playerQuit(const std::string &username)
{
    setConfirmationState(username, false);
}

bool GameHandler::areAllPlayersConfirmed() const
{
    std::cout << "GameHandler::areAllPlayersConfirmed: " << numberOfConfirmedPlayers() << "   " << m_players.size() << std::endl;
    return numberOfConfirmedPlayers() == m_players.size();
}

bool GameHandler::areAllPlayersConnected() const
{
    bool allConnected {true};

    for (auto &player : m_players)
        allConnected = allConnected && m_userHub->isConnected(player);

    std::cout << "GameHandler::areAllPlayersConnected: " << allConnected << std::endl;

    return allConnected;
}

bool GameHandler::areAllPlayersNotInGame() const
{
    bool allNotInGame {true};

    for (auto &player : m_players)
        allNotInGame = allNotInGame && m_userHub->isInGame(player);

    std::cout << "GameHandler::areAllPlayersNotInGame: " << allNotInGame << std::endl;

    return allNotInGame;
}

void GameHandler::start()
{
    auto startRequest {SerializableMessageFactory::serializeGameStarted(getID(), json::parse(m_configuration))};

    for (auto &p : m_players)
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
    for (const auto &i_player : m_players) {
        std::cout << "Saving " << i_player << std::endl;
        DatabaseHandler::addGameIdToUser(i_player, getID());
    }

    DatabaseHandler::setGameBoardConfig(getID(), json::parse(m_configuration)["board_config"]);
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
    auto request(json::parse(serRequest));

    if (request["action"] == toJsonString(GameAction::SURRENDER)) {

    } else if (request["action"] == toJsonString(GameAction::PROPOSE_SAVE)) {
        m_isFinished = true;

    } else if (request["action"] == toJsonString(GameAction::END_GAME)) {
        updateELO(request["winner"]);
        m_isFinished = true;
    }

    for (auto &p : m_players)
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

    auto gameHandleIt {std::find_if(m_games.begin(), m_games.end(), [gameID](const auto &g) { return (int)g->getID() == (int)gameID; })};

    if (gameHandleIt != m_games.end())
        gameHandle = *gameHandleIt;

    std::cout << "GameHub::getGame: " << gameHandle << std::endl;

    return gameHandle;
}

void GameHub::eraseFinished()
{
    m_games.erase(std::remove_if(m_games.begin(), m_games.end(), [](auto &g) { return g->isFinished(); }), m_games.end());
}

void GameHub::processGameCreation(const std::string &serRequest)
{
    auto request = json::parse(serRequest);

    auto gameID {getUniqueID()};
    std::vector<std::string> gPlayers;
    for (auto &i_user : request["receivers"]) {
        gPlayers.push_back(i_user.get<std::string>());
    }

    DatabaseHandler::createGame(gameID, gPlayers, (int)gPlayers.size(), request["game_configuration"]);
    auto tmp {std::make_shared<GameHandler>(gameID, this, m_userHub)};

    // This add the players to the game
    auto boardConfig = DatabaseHandler::getGameConfig(gameID);
    tmp->setConfiguration(boardConfig.dump());
    tmp->playerJoined(request["sender"].get<std::string>());
    tmp->saveToDB();

    m_games.push_back(tmp);

    request["game_id"] = gameID;
    for (auto &i_user : request["receivers"]) {
        if (i_user.get<std::string>() != request["sender"].get<std::string>()) {
            m_userHub->relayMessageTo(i_user.get<std::string>(), request.dump());
        }
    }
}

void GameHub::createGameFromDB(int gameID)
{
    auto tmp {std::make_shared<GameHandler>(gameID, this, m_userHub)};

    auto config = DatabaseHandler::getGameConfig(gameID);
    tmp->setConfiguration(config.dump());

    m_games.push_back(tmp);
}

void GameHub::processGameJoin(const std::string &serRequest)
{
    auto request = json::parse(serRequest);
    auto targetGame {getGame(request["game_id"].get<int>())};

    if (!targetGame) {
        createGameFromDB(request["game_id"].get<int>());
        targetGame = getGame(request["game_id"].get<int>());
    }
    std::cout << "target " << &targetGame << std::endl;

    targetGame->playerJoined(request["username"].get<std::string>());

    if (targetGame->areAllPlayersConfirmed() && targetGame->areAllPlayersConnected() && targetGame->areAllPlayersNotInGame()) {
        std::cout << "Starting game " << std::endl;
        targetGame->start();
    }
}

void GameHub::processGameQuit(const std::string &serRequest)
{
    auto request(json::parse(serRequest));
    auto targetGame {getGame(request["game_id"])};

    targetGame->playerJoined(request["username"]);

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
