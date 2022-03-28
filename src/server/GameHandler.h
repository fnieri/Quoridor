/**
 * @file GameHandler.h
 * @author Boris Petrov
 * @brief Handler of requests related to a game
 * @date 02/25/22
 */

#pragma once

#include "UserHandler.h"
#include "src/client/Board.h"
#include "src/common/Observer.h"

#include <memory>
#include <mutex>
#include <vector>

class GameHub;
class WallAction;
class PlayerAction;
class GameModel;

class GameHandler
{
private:
    int m_gameID;
    bool m_isFinished {false};

    GameHub *m_gameHub;
    UserHub *m_userHub;

    int m_confirmedPlayers {0};
    int m_saveAcceptance {0};

    std::shared_ptr<GameModel> m_gameModel;

    mutable std::mutex m_gameHandlerMutex;

    /* void setConfirmationState(const std::string &, bool); */

public:
    /**
     * @param gameId identifier of the game, should be unique
     * @param userHub user hub used to access the participants
     */
    GameHandler(int id, GameHub *, UserHub *, const std::vector<std::string> &players);
    GameHandler(int id, GameHub *, UserHub *, const std::string &config);
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

    void playerJoined(const std::string &);
    void playerQuit(const std::string &);

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
