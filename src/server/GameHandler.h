/**
 * @file GameHandler.h
 * @author Boris Petrov
 * @brief Handler of requests related to a game
 * @date 02/25/22
 */

#pragma once

#include "UserHandler.h"
#include "src/common/Observer.h"

class GameHandler
{
private:
    int m_gameID;
    bool m_isFinished {false};

    GameHub *m_gameHub;
    UserHub *m_userHub;

    std::vector<std::string> m_players;
    std::array<bool, 4> m_confirmedPlayers;

    bool areAllPlayersConfirmed() const;
    bool areAllPlayersConnected() const;
    bool areAllPlayersNotInGame() const;

public:
    /**
     * @param gameId identifier of the game, should be unique
     * @param userHub user hub used to access the participants
     */
    GameHandler(int, GameHub *, UserHub *);

    int getID() const noexcept;
    bool isFinished() const;

    void addPlayer(const std::string &);
    void confirmPlayer(const std::string &);

    bool canStart();
    void start();

    /**
     * In order to relay the message only to those needing it (i.e.
     * not the sender), the username of the sender is also passed
     * to the method.
     */
    void processRequest(const std::string &, const std::string &);
};

class GameHub
{
private:
    /**
     * Needed to see if users are indeed connected and
     * access their handlers.
     */
    UserHub *m_userHub;
    std::vector<std::shared_ptr<GameHandler>> m_games;

    int getUniqueID() const;
    auto getGame(int) const;

public:
    GameHub(UserHub *);

    /**
     * Create game with two users' usernames.
     */
    /* void createGame(std::initializer_list<std::string>); */
    void createAndRelayGameFromInvite(const std::string &);
    void eraseFinished();

    void processRequest(const std::string &);
};
