/**
 * @file GameHandler.h
 * @author Boris Petrov
 * @brief Handler of requests related to a game
 * @date 02/25/22
 */

#pragma once

#include "UserHandler.h"
#include "src/common/Observer.h"

class GameHandler : public Subject
{
private:
    bool m_isPlaying {false};
    UserHub *m_userHub;
    std::vector<std::string> m_players;

public:
    GameHandler(UserHub *, std::initializer_list<std::string>);

    bool isFinished() const
    {
        return m_isPlaying;
    }

    /**
     * In order to relay the message only to those needing it (i.e.
     * not the sender), the username of the sender is also passed
     * to the method.
     */
    void processMessage(const std::string &, const std::string &);
};

class GameHub : public Observer
{
private:
    /**
     * Needed to see if users are indeed connected and
     * access their handlers.
     */
    UserHub *m_userHub;
    std::vector<GameHandler> m_games;

public:
    GameHub(UserHub *);

    void update(Event) override;
    /**
     * Create game with two users' usernames.
     */
    void createGame(std::initializer_list<std::string>);
    void eraseFinished();
};
