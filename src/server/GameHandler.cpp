/**
 * @file GameHandler.cpp
 * @author Boris Petrov
 * @brief Handler of requests related to a game
 * @date 02/25/22
 */

#include "GameHandler.h"

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

void GameHandler::addPlayer(const std::string &username)
{
    m_players.push_back();

    assert(m_players.size() <= 4);
}

void GameHandler::confirmPlayer(const std::string &username)
{
    for (auto i {0}; i < m_players.size(); ++i) {
        if (m_players[i] == username) {
            m_confirmedPlayers[i] = true;
            break;
        }
    }
}

bool GameHandler::areAllPlayersConfirmed() const
{
    bool allConfirmed {true};

    for (auto &state : m_confirmedPlayers)
        allConfirmed = allConfirmed && state;

    return allConfirmed;
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

bool GameHandler::canStart() const
{
    return allConfirmed() && allConnected() && allNotInGame();
}

void GameHandler::start()
{
    auto startRequest {SerializableMessageFactory::getGameStarted(m_configuration)};

    for (auto &p : m_players)
        m_userHub->relayMessageTo(p, startRequest);
}

void GameHandler::processRequest(const std::string &sender, const std::string &serMessage)
{
    auto message {json::parse(serMessage)};

    // TODO: handle
    // - endgame

    for (auto &p : m_players)
        if (p != sender)
            m_userHub->relayMessageTo(p, serMessage);
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

    while (DatabaseHandler::doesIDExist()) {
        ID = std::rand()
    }

    return ID;
}

auto GameHub::getGame(int gameID) const
{
    std::shared_ptr<GameHandler> gameHandle;

    auto gameHandleIt {std::find_if(m_games.begin(), m_games.end(), [gameID](const auto &g) { return g->getID() == gameID; })};

    if (gameHandleIt != m_games.end())
        userHandler = *gameHandleIt;

    return gameHandle;
}

/* void GameHub::createGame(std::initializer_list<std::string> players) */
/* { */
/*     GameHandler tmp {m_userHub, std::move(players)}; */
/*     tmp.registerObserver(this); */

/*     m_games.push_back(std::move(tmp)); */
/* } */

void GameHub::createAndRelayGameFromInvite(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    auto gameID {getUniqueID()};

    auto tmp {std::make_shared<GameHandler>(gameID, this, m_userHub};

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

void GameHub::eraseFinished()
{
    m_games.erase(std::remove_if(m_games.begin(), m_games.end(), [](auto &g) { return g.isFinished(); }), m_games.end());
}

void GameHub::processRequest(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    if (request["action"] == toJsonString(GameSetup::GAME_INVITE)) {
        createAndRelayGameFromInvite(serRequest);

    } else if (request["action"] == toJsonString(GameSetup::GAME_ACCEPT_INVITATION)) {
        auto targetGame {getGame(requets["game_id"])};
        targetGame->confirmPlayer(request["username"]);
        if (targetGame->canStart()) {
            targetGame->start();
        }

    } else if (request["action"] == toJsonString(GameSetup::GAME_REFUSE_INVITATION)) {
        auto targetGame {getGame(requets["game_id"])};
        targetGame->playerRefused(request["username"]); // TODO
    }
}
