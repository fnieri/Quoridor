/**
 * @file GameHandler.h
 * @author Boris Petrov
 * @brief Handler of requests related to a game
 * @date 02/25/22
 */

#pragma once

#include "UserHandler.h"
#include "src/common/Observer.h"

#include <vector>
#include <memory>
#include <mutex>

class GameHub;

class GameHandler
{
private:
    int m_gameID;
    bool m_isFinished {false};

    GameHub *m_gameHub;
    UserHub *m_userHub;

    std::string m_configuration;
    std::vector<std::string> m_players;
    std::array<bool, 4> m_confirmedPlayers;

    void setConfirmationState(const std::string &, bool);

public:
    /**
     * @param gameId identifier of the game, should be unique
     * @param userHub user hub used to access the participants
     */
    GameHandler(int, GameHub *, UserHub *);
    /**
     * @brief Get the ID of current Game
     * @return m_gameID gameID
     */
    int getID() const noexcept;
    /**
     * @brief Return if game is finished
     * @return m_isFinished
     */
    bool isFinished() const;
    /**
     * @brief Set a game configuration given a configuration passed by parameter
     * @param configuration gameConfiguration
     */
    void setConfiguration(const std::string &);
    /**
     * @brief Add a player given its username
     * @param username player's username
     */
    void addPlayer(const std::string &);

    void confirmPlayer(const std::string &);
    void cancelPlayer(const std::string &);
    int numberOfConfirmedPlayers() const;
    /**
     * @brief Check if all players in a game have confirmed to want to play
     * @return True if allConfirmed, else false
     */
    bool areAllPlayersConfirmed() const;
    /**
     * @brief Check if all players in a game are connected to server
     * @return allConnected True if allConnected, else false
     */
    bool areAllPlayersConnected() const;
    bool areAllPlayersNotInGame() const;
    /**
     * @brief Update ELOs for all players involved in a game given a winner
     * @param winner Username of winner
     */
    void updateELO(const std::string &);
    /**
     * @brief Relay message to all players that the game has started
     */
    void start();
    /**
     * @brief Inform all players that the game has terminated
     */
    void terminate();
    /**
     * @brief Delete game from DataBase
     */
    void deleteFromDB();
    /**
     * @brief Save current game to Database along with configuration
     */
    void saveToDB();

    /**
     * In order to relay the message only to those needing it (i.e.
     * not the sender), the username of the sender is also passed
     * to the method.
     */
    void processRequest(const std::string &);
};

class GameHub
{
private:
    /**
     * Needed to see if users are indeed connected and
     * access their handlers.
     */
    UserHub *m_userHub;

    std::mutex m_gamesMutex;
    std::vector<std::shared_ptr<GameHandler>> m_games;

    int getUniqueID() const;

    /**
     * @brief Process the request of a game creation by an user
     * @param std::string serRequest serializedRequest as string, as it is coming from user
     */
    void processGameCreation(const std::string &);
    /**
     * @brief Process the request of an user joining a game
     * @param std::string serRequest serializedRequest as string, as it is coming from user
     */
    void processGameJoin(const std::string &);
    /**
     * @brief Process the request of an user leaving a game
     * @param std::string serRequest serializedRequest as string, as it is coming from user
     */
    void processGameQuit(const std::string &);
    /**
     * @brief Create a game from a gameID in Database, by retrieving the configuration
     * @param int gameID ID of the requested Game
     */
    void createGameFromDB(int);
    /**
     * @brief Remove a game, given its gameID
     * @param int gameID
     */
    void unloadGame(int);

public:
    GameHub(UserHub *);

    std::shared_ptr<GameHandler> getGame(int) const;
    /**
     * @brief Erase a finished game
     */
    void eraseFinished();

    void processRequest(const std::string &);
};
