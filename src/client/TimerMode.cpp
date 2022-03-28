#include "TimerMode.h"
#include "src/common/SerializableMessageFactory.h"

#include <cassert>
#include <chrono>
#include <cmath>
#include <mutex>
#include <thread>

using namespace std::chrono;
using json = nlohmann::json;

TimerMode::TimerMode(int nPlayers, int increment, int time, std::vector<std::string> &players)
    : c_increment {increment}
{
    assert(nPlayers == 2 | nPlayers == 4);
    for (int i = 0; i < nPlayers; i++) {
        m_timers.emplace_back(time);
    }
    for (auto &player : players)
        m_players.push_back(player);
}

TimerMode::TimerMode(int increment, std::vector<float> &timers, std::vector<std::string> &players)
    : c_increment {increment}

{
    assert(timers.size() == 2 || timers.size() == 4);
    for (auto &timer : timers)
        m_timers.emplace_back(timer);
    for (auto &player : players)
        m_players.push_back(player);
}

TimerMode::TimerMode(const std::string &gameConfig)
{
    auto conf = json::parse(gameConfig);
    int nOfPlayers = conf["n_players"];
    for (int i = 0; i < nOfPlayers; i++) {
        std::string playerString = "player" + std::to_string(i);

        m_timers.emplace_back((conf[playerString]["time"]));
        m_players.emplace_back(conf[playerString]["username"]);
    }
    c_increment = conf["increment"];
}

TimerMode::TimerMode(const TimerMode &other)
    : m_players {other.m_players}
    , c_increment {other.c_increment}
    , m_stopTimer {true}
{
    m_timers = std::deque<std::atomic<float>>();
    // for (auto& timer : other.m_timers) m_timers.push_back(timer);
    for (int i = 0; i < other.m_timers.size(); i++) {
        float tmp = other.m_timers.at(i);
        m_timers.emplace_back(tmp);
    }
}

TimerMode &TimerMode::operator=(const TimerMode &other)
{
    m_timers = std::deque<std::atomic<float>>();
    for (int i = 0; i < other.m_timers.size(); i++) {
        float tmp = other.m_timers.at(i);
        m_timers.emplace_back(tmp);
    }
    m_players = other.m_players;
    c_increment = other.c_increment;
    m_stopTimer = true;
    return *this;
}

std::string TimerMode::switchPlayer(int newPlayer)
{
    setStopTimer(true); // Stop current threading timer
    std::this_thread::sleep_for(32000us); // Wait for worst case scenario for others clock to stop
    setStopTimer(false);
    std::string timeLeft = countTime(newPlayer);
    return timeLeft;
}

std::string TimerMode::countTime(int playerID)
{
    while (!m_stopTimer && m_timers.at(playerID) > 0.0f) // While true is done for each frame
    // 16660 = 1/60 s = 1 frame

    {
        std::this_thread::sleep_for(16600us);
        m_timers.at(playerID) = m_timers.at(playerID) - 0.0167; // att francesco jai un problm avce ce -= ????
    }
    setStopTimer(false);
    float oldTimer = m_timers.at(playerID);
    if (oldTimer <= 0)
        timesUp(playerID);
    else {
        m_timers.at(playerID) = ceil(m_timers.at(playerID));
        m_timers.at(playerID) = m_timers.at(playerID) + c_increment;
    }
    json returnJson = {{"time_left", (int)m_timers.at(playerID)}, {"player_id", playerID}};
    return returnJson.dump();
}

std::string TimerMode::timesUp(int playerID)
{
    json msg = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::SURRENDER, m_players.at(playerID));
    return msg.dump();
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
    json timerJson = {{"timers", timersArray}, {"increment", c_increment}};
    return timerJson;
}

json TimerMode::saveGame()
{
    return serialized();
}

int TimerMode::getTimeLeft(int playerID)
{
    return (int)m_timers.at(playerID);
}

void TimerMode::setPlayerTimer(int playerID, int time)
{
    m_timers.at(playerID) = (float)time;
}