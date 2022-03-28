#pragma once

#include "src/common/Serializable.h"

#include <nlohmann/json.hpp>

#include <atomic>
#include <deque>
#include <mutex>
#include <string>
#include <vector>

class TimerMode : public Serializable
{
    std::deque<std::atomic<float>> m_timers;
    std::vector<std::string> m_players;
    int c_increment {};
    std::atomic<bool> m_stopTimer = true;

public:
    /**
     * @brief Constructor when initialising a game
     * @param int increment The increment of the current game
     * @param int nPlayers The number of players
     * @param int
     * @throw AssertionError If nPlayers != 2 or 4
     */
    TimerMode(int nPlayers, int increment, int time, std::vector<std::string> &players);

    /**
     * @brief Constructor used when resuming a game
     * @param int increment The increment of the current game
     * @param std::vector<float> timers, the timers of all players
     * @throw AssertionError If timers is not of length 2 or 4
     */
    TimerMode(int increment, std::vector<float> &timers, std::vector<std::string> &players);

    TimerMode(const TimerMode &);
    TimerMode &operator=(const TimerMode &other);

    TimerMode() = default;

    explicit TimerMode(const std::string &);

    /**
     * @brief Switch player's turn in timer
     * @param newPlayer Player that needs to play
     * @details Wait one frame and a few nanoseconds more before switching the turn
     * This is to make sure that the other player's timer has stopped before starting another
     * player's time. OldPlayer timer will stop on its own
     */
    auto switchPlayer(int newPlayer) -> std::string;

    /**
     * @brief Saves the timer if game is paused
     *
     */
    auto serialized() -> nlohmann::json override;

    /**
     * @brief Calculate how much time a user spent to make a move
     *
     * @param playerID The player's index in the players' time vector (m_timers)
     */
    auto countTime(int playerID) -> std::string;

    /**
     * @brief Sends a message to the server to indicate that a certain player has reached his time limit
     *
     * @param playerID The player's index in the players' time vector (m_timers)
     * @return std::string The message in json format as a string
     */
    auto timesUp(int playerID) -> std::string;

    /**
     * @brief Converts the time represented as a float in this class to a string for the view
     *
     * @param playerID The player's index in the players' time vector (m_timers)
     * @return std::string The time in string
     */
    auto toTimerString(int playerID) -> std::string;

    /**
     * @brief Set the boolean m_stopTimer to true, if it is set to true, the current ticking timer will stop
     *
     */
    auto setStopTimer(bool) -> void;

    auto saveGame() -> nlohmann::json;

    auto getTimeLeft(int playerID) -> int;

    auto setPlayerTimer(int playerID, int time) -> void;
};