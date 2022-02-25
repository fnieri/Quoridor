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

GameHandler::GameHandler(UserHub *userHub, std::initializer_list<std::string> players)
    : m_userHub {userHub}
{
    assert(players.size() == 2); // for now, maybe more in the future

    for (auto &i : players)
        m_players.push_back(i);
}

void GameHandler::processMessage(const std::string &sender, const std::string &serMessage)
{
    auto message {json::parse(serMessage)};

    // TODO: handle
    // - accept
    // - refuse
    // - endgame

    // Messages relayed to one another: temp chat, actions, etc.
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

void GameHub::update(Event e)
{
    switch (e) {
    case Event::Modified:
        eraseFinished();
        break;
    default:
        break;
    }
}

void GameHub::createGame(std::initializer_list<std::string> players)
{
    GameHandler tmp {m_userHub, std::move(players)};
    tmp.registerObserver(this);

    m_games.push_back(std::move(tmp));
}

void GameHub::eraseFinished()
{
    m_games.erase(std::remove_if(m_games.begin(), m_games.end(), [](auto &g) { return g.isFinished(); }), m_games.end());
}
