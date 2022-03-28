//
// Created by frann on 25/03/22.
//

#include <catch2/catch.hpp>

#include "src/client/TimerMode.h"
#include <chrono>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <unistd.h>

using json = nlohmann::json;
using namespace std::chrono_literals;

SCENARIO("Timer mode game")
{
    GIVEN("A 4 players' timer game with 10 minutes and 2 sec increment")
    {
        int startingTime = 600;
        int nPlayers = 4;
        int increment = 2;
        std::vector<std::string> players {"sarah", "lolo", "bob", "ola"};
        TimerMode tMode {nPlayers, increment, startingTime, players};

        WHEN("Starting a game from the first player")
        {
            std::thread P1Thread(&TimerMode::switchPlayer, &tMode, 0);
            sleep(5);
            usleep(16600);
            std::thread stop(&TimerMode::setStopTimer, &tMode, true);
            stop.join();
            P1Thread.join();

            THEN("Stopping timer after 5 seconds and a bit (for precision) should have player 0's time down by 3")
            {
                int P1TimeLeft = tMode.getTimeLeft(0);
                REQUIRE(P1TimeLeft == startingTime - 3);
            }
            THEN("All other players should still be at 600")
            {
                for (int i = 1; i < nPlayers; i++) {
                    REQUIRE(tMode.getTimeLeft(i) == startingTime);
                }
            }
            THEN("Showing the time left of a player")
            {
                std::string tLeft = "9 : 57"; // 10 minutes - 5 seconds of play time + 2 second for increment for the first player
                REQUIRE(tLeft == tMode.toTimerString(0));
            }
        }

        WHEN("Switching to player 1 and then testing in game switching ")
        {
            std::thread P2Thread(&TimerMode::switchPlayer, &tMode, 1);
            std::this_thread::sleep_for(100ms);
            std::thread switchPlayer(&TimerMode::switchPlayer, &tMode, 2);
            switchPlayer.detach();
            P2Thread.join();
            THEN("If player 2 plays his action instantaneously, his timer should be starting time + increment")
            {
                REQUIRE(tMode.getTimeLeft(1) == startingTime + increment);
            }
        }
    }
}
