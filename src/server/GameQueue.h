/**
 * @file GameQueue.h
 * @author Boris Petrov
 * @brief Queue handling the matchmaking of players
 * @date 02/25/22
 */

#pragma once

enum class GameMode { Classic };

class GameQueue
{
private:
    GameMode m_mode;
    std::vector<std::string> m_queuedPlayers;

public:
    GameQueue(GameMode);
    /**
     * Continuously runs and creates games with
     * queued players
     */
    void match();
    /**
     * @brief Add username to queue
     * @param user Username of user to add to queue
     */
    void queueUser(const std::string &);
};
