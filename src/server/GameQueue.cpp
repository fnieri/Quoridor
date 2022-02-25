/**
 * @file GameQueue.cpp
 * @author Boris Petrov
 * @brief Queue handling the matchmaking of players
 * @date 02/25/22
 */

#include "GameQueue.h"

GameQueue::GameQueue(GameMode mode)
    : m_mode {mode}
{
    std::thread th {match};
    th.detach();
}

void GameQueue::match()
{
    while (true) {
        sleep(0.5); // interval between each matchmaking attempt
    }
}

void GameQueue::queueUser(const std::string &user)
{
    m_queuedPlayers.push_back(user);
}
