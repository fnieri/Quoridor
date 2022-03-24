#include "TimerMode.h"
#include <cassert>
#include <iostream>
#include <math.h>
#include <thread>
#include <unistd.h>

using json = nlohmann::json;

TimerMode::TimerMode(int nPlayers, int increment, int time)
    : c_increment {increment}
{
    assert(nPlayers == 2 | nPlayers == 4);
    std::vector<float> tmp(nPlayers, (float)time);
    m_timers = tmp;
}

TimerMode::TimerMode(int increment, std::vector<float> timers)
    : c_increment {increment}
    , m_timers {timers}
{
    assert(timers.size() == 2 || timers.size() == 4);
}

void TimerMode::startGame()
{
    switchPlayer(0);
}

void TimerMode::switchPlayer(int newPlayer)
{
    setStopTimer(true); // Stop current threading timer
    usleep(18000); // Wait for worst case scenario for others clock to stop
    setStopTimer(false);
    std::thread playerTimer(&TimerMode::countTime, this, newPlayer);
    playerTimer.detach();
}

void TimerMode::countTime(int playerID)
{
    while (!m_stopTimer && m_timers.at(playerID) > 0) // While true is done for each frame
                                                      // 16660 = 1/60 s = 1 frame
    {
        usleep(16660);
        m_timers.at(playerID) -= 0.016666666666;
    }
    setStopTimer(false);
    std::cout << toTimerString(playerID) << "ee" << std::endl;
    if (m_timers.at(playerID) == 0)
        timesUp(playerID);
    else {
        m_timers.at(playerID) = ceil(m_timers.at(playerID));
        m_timers.at(playerID) += c_increment;
    }
    std::cout << toTimerString(playerID) << "ee" << std::endl;
}

std::string TimerMode::timesUp(int playerID)
{
    return "";
    // send msg to server so he knows one of the player has reached its time limit
}

std::string TimerMode::toTimerString(int playerID)
{
    int playerTime = (int)m_timers.at(playerID);
    short int minutes = playerTime / 60;
    short int seconds = playerTime % 60;

    return std::to_string(minutes) + " : " + std::to_string(seconds);
}

void TimerMode::setStopTimer(bool newState)
{
    m_stopTimer = newState;
}

json TimerMode::serialized()
{
    json timersArray;
    for (int i = 0; i < m_timers.size(); i++) {
        std::string playerString = "player_" + std::to_string(i);
        timersArray[playerString] = (int)m_timers.at(i);
    }
    timersArray["n_players"] = m_timers.size();
    return timersArray;
}
