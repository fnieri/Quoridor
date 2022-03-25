#include "TimerMode.h"
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

using namespace std::chrono;
using json = nlohmann::json;

TimerMode::TimerMode(int nPlayers, int increment, int time)
    : c_increment {increment}
{
    assert(nPlayers == 2 | nPlayers == 4);
    for (int i = 0; i < nPlayers; i++) {
        m_timers.emplace_back(time);
    }
}

TimerMode::TimerMode(int increment, std::vector<float> &timers)
    : c_increment {increment}

{
    assert(timers.size() == 2 || timers.size() == 4);
    for (auto &timer : timers)
        m_timers.emplace_back(timer);
}

TimerMode::TimerMode(const std::string &gameConfig)
{
    auto conf = json::parse(gameConfig);
    int nOfPlayers = conf["n_players"];
    for (int i = 0; i < nOfPlayers; i++) {
        std::string playerString = "player" + std::to_string(i);
        m_timers.emplace_back((conf[playerString]));
    }
    c_increment = conf["increment"];
}

void TimerMode::switchPlayer(int newPlayer)
{
    setStopTimer(true); // Stop current threading timer
    std::this_thread::sleep_for(20000us); // Wait for worst case scenario for others clock to stop
    setStopTimer(false);
    std::thread playerTimer(&TimerMode::countTime, this, newPlayer);
    playerTimer.detach();
}

void TimerMode::countTime(int playerID)
{
    auto start = high_resolution_clock::now();

    while ((!m_stopTimer) && m_timers.at(playerID) > 0) // While true is done for each frame
                                                        // 16660 = 1/60 s = 1 frame
    {
        std::this_thread::sleep_for(16660us);
        m_timers.at(playerID) = m_timers.at(playerID) - 0.016666666666; // att francesco jai un problm avce ce -= ????
    }
    std::cout << "I have stopped!! : " << m_timers.at(playerID) << " for player " << playerID << std::endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time of loop : " << duration.count() << std::endl;

    setStopTimer(false);

    float oldTimer = m_timers.at(0);
    if (oldTimer <= 0)
        timesUp(playerID);
    else {
        std::cout << "I have updated " << oldTimer << std::endl;
        m_timers.at(playerID) = ceil(m_timers.at(playerID));
        m_timers.at(playerID) = oldTimer;
    }
    std::cout << "I am done! Player" << playerID << std::endl;
}

std::string TimerMode::timesUp(int playerID)
{
    return "";
    // send msg to server so he knows one of the player has reached its time limit
}

std::string TimerMode::toTimerString(int playerID)
{
    auto playerTime = (short)m_timers.at(playerID);
    short minutes = playerTime / 60;
    short seconds = playerTime % 60;

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
    timersArray["increment"] = c_increment;
    return timersArray;
}

json TimerMode::saveGame()
{
    return serialized();
}

int TimerMode::getTimeLeft(int playerID)
{
    // m_mutex.lock();
    float toRet = m_timers.at(playerID);
    // m_mutex.unlock();
    return (int)toRet;
}