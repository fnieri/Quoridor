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
    std::cout << "GameHandler::playerJoined: " << username << std::endl;
    m_confirmedPlayers++;
}

void GameHandler::playerQuit(const std::string &username)
{
    // Maybe inform other players ?
    std::cout << "GameHandler::playerQuit: " << username << std::endl;
    m_confirmedPlayers--;
}

bool GameHandler::areAllPlayersConfirmed() const
{
    std::cout << "GameHandler::areAllPlayersConfirmed: " << numberOfConfirmedPlayers() << "   " << m_gameModel->getPlayersCount() << std::endl;
    return numberOfConfirmedPlayers() == m_gameModel->getPlayersCount();
}

bool GameHandler::areAllPlayersConnected() const
{
    bool allConnected {true};

    for (auto &player : m_gameModel->getPlayersNames())
        allConnected = allConnected && m_userHub->isConnected(player);

    std::cerr << std::boolalpha << "GameHandler::areAllPlayersConnected: " << allConnected << std::endl;

    return allConnected;
}

bool GameHandler::areAllPlayersNotInGame() const
{
    bool allNotInGame {true};

    for (auto &player : m_gameModel->getPlayersNames())
        allNotInGame = allNotInGame && !m_userHub->isInGame(player);

    std::cerr << std::boolalpha << "GameHandler::areAllPlayersNotInGame: " << allNotInGame << std::endl;

    return allNotInGame;
}

void GameHandler::start()
{
    auto startRequest = SerializableMessageFactory::serializeGameStarted(getID(), m_gameModel->serialized());

    /* startRequest["chat"] = DatabaseHandler::getMessages(getID()); */
    startRequest["chat"] = std::vector<std::vector<std::string>> {
        {"Jean-Charles", "Salutations à vous"                                           },
        {"Ernest",       "Ç'eût été mieux si vous eûtes joué autre chose, camarade"}
    };

    for (auto &p : m_gameModel->getPlayersNames())
        m_userHub->relayMessageTo(p, startRequest.dump());
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
    DatabaseHandler::setGameBoardConfig(getID(), m_gameModel->serialized());
}

void GameHandler::updateELO(const std::string &winner)
{
    std::vector<float> currentELOs;
    std::vector<bool> winningState;

    auto gameConf = DatabaseHandler::getGameConfig(getID());

    for (auto &i_player : gameConf["players"]) {
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

std::string GameHandler::processAndGetAnswerForSurrender(const json &request)
{
    m_gameModel->playerSurrendered(request["sender"]);

    return processEndGameEval(request);
}

std::string GameHandler::processAndGetAnswerForAction(const json &request)
{
    m_gameModel->processAction(request["move"].dump());

    m_gameModel->debugPrintBoard();

    return processEndGameEval(request);
}

std::string GameHandler::processEndGameEval(const json &request)
{
    auto answer {request.dump()};

    if (m_gameModel->hasWinner()) {
        updateELO(m_gameModel->getWinner());
        deleteFromDB();
        m_isFinished = true;

        answer = GameRelatedActionsSerializableMessageFactory::serializeGameEnded(getID()).dump();
    }

    return answer;
}

std::string GameHandler::processAndGetAnswerForSave(const json &request)
{
    auto answer = request.dump();

    if (request["action"] == toJsonString(GameAction::PROPOSE_SAVE) || request["action"] == toJsonString(GameAction::ACCEPT_SAVE)) {
        m_saveAcceptance++;

    } else if (request["action"] == toJsonString(GameAction::REFUSE_SAVE)) {
        m_saveAcceptance--;
    }

    return answer;
}

void GameHandler::processRequest(const std::string &serRequest)
{
    std::lock_guard<std::mutex> guard {m_gameHandlerMutex};

    auto request(json::parse(serRequest));
    auto answer {serRequest};

    if (request["action"] == toJsonString(GameAction::SURRENDER)) {
        processAndGetAnswerForSurrender(request);

    } else if (request["action"] == toJsonString(JsonPlayerAction::MOVE_PAWN) || request["action"] == toJsonString(JsonPlayerAction::PLACE_WALL)) {
        std::cerr << "INSIDE ACTION\n";
        processAndGetAnswerForAction(request);

    } else if (request["action"] == toJsonString(GameAction::PROPOSE_SAVE) || request["action"] == toJsonString(GameAction::ACCEPT_SAVE)
        || request["action"] == toJsonString(GameAction::REFUSE_SAVE)) {
        processAndGetAnswerForSave(request);
    }

    for (auto &p : m_gameModel->getPlayersNames())
        if (p != request["sender"])
            m_userHub->relayMessageTo(p, answer);

    std::cerr << "After relaying\n";

    if (m_isFinished)
        m_gameHub->eraseFinished();
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

    std::cerr << "GameHub::getGame: " << gameHandle << std::endl;

    return gameHandle;
}

void GameHub::eraseFinished()
{
    m_games.erase(std::remove_if(m_games.begin(), m_games.end(), [](auto &g) { return g->isFinished(); }), m_games.end());
}

void GameHub::processGameCreation(const std::string &serRequest)
{
    auto request = json::parse(serRequest);

    auto gameID = getUniqueID();
    request["game_id"] = gameID;

    // Establish players usernames
    std::vector<std::string> gPlayers {request["sender"]};
    for (auto &i_user : request["receivers"]) {
        gPlayers.push_back(i_user.get<std::string>());
    }

    // Add to database
    DatabaseHandler::createGame(gameID, gPlayers, (int)gPlayers.size(), request["game_configuration"]);
    for (const auto &i_player : gPlayers) {
        std::cerr << "Saving " << i_player << std::endl;
        DatabaseHandler::addGameIdToUser(i_player, gameID);
    }

    auto config = request["game_configuration"].dump();
    auto tmp = std::make_shared<GameHandler>(gameID, this, m_userHub, config);

    tmp->saveToDB();
    m_games.push_back(tmp);

    // Inform the players
    m_userHub->relayMessageTo(request["sender"], request.dump());
    for (auto &i_user : request["receivers"]) {
        m_userHub->relayMessageTo(i_user, request.dump());
    }
}

void GameHub::createGameFromDB(int gameID)
{
    auto config {DatabaseHandler::getGameConfig(gameID)["board_config"].dump()};
    auto tmp {std::make_shared<GameHandler>(gameID, this, m_userHub, config)};

    std::cerr << "GameHub::createGameFromDB " << tmp << std::endl;

    m_games.push_back(tmp);
}

void GameHub::processGameJoin(const std::string &serRequest)
{
    std::cerr << "GameHub::processGameJoin\n";

    auto request = json::parse(serRequest);
    auto targetGame {getGame(request["game_id"].get<int>())};

    if (!targetGame) {
        std::cerr << "GameHub::processGameJoin no game with id\n";

        createGameFromDB(request["game_id"].get<int>());
        targetGame = getGame(request["game_id"].get<int>());
    }

    std::cout << "GameHub::processGameJoin target = " << targetGame << std::endl;

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

    if (targetGame) {
        targetGame->playerQuit(request["username"]);

        if (targetGame->numberOfConfirmedPlayers() == 0) {
            unloadGame(request["game_id"]);
        }
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

    std::cerr << "BEFORE ACTION ptr = " << this << "userHub_ptr = " << m_userHub << std::endl;

    if (request["action"] == toJsonString(GameSetup::CREATE_GAME)) {
        processGameCreation(serRequest);

    } else if (request["action"] == toJsonString(GameSetup::JOIN_GAME)) {
        processGameJoin(serRequest);

    } else if (request["action"] == toJsonString(GameSetup::QUIT_GAME)) {
        processGameQuit(serRequest);
    }

    std::cerr << "AFTER ACTION\n";
}
