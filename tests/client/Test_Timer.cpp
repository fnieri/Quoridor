//
// Created by frann on 25/03/22.
//

#include <catch2/catch.hpp>

#include "src/client/TimerMode.h"
#include <nlohmann/json.hpp>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

SCENARIO("Timer mode game")
{
    GIVEN("A 4 players' timer game with 10 minutes and 2 sec increment")
    {
        int startingTime = 600;
        int nPlayers = 4;
        int increment = 2;
        TimerMode tMode{nPlayers, increment, startingTime};
        WHEN("Starting a game from the first player")
        {
            std::thread P1Thread(&TimerMode::switchPlayer, &tMode, 0);

            sleep(5);
            usleep(100000);
            tMode.setStopTimer(true);
            P1Thread.detach();
            usleep(500000);
            THEN("Stopping timer after 5 seconds and a bit (for precision) should have player 0's time down by 3")
            {
                int P1TimeLeft = tMode.getTimeLeft(0);
                REQUIRE(P1TimeLeft == startingTime - 3);

            }
            THEN("All other players should still be at 600")
            {
                for (int i = 1; i < nPlayers; i++)
                {
                    REQUIRE(tMode.getTimeLeft(i) == startingTime);
                }
            }
            THEN("Showing the time left of a player")
            {
                std::string tLeft = "9 : 57";      // 10 minutes - 5 seconds of play time + 2 second for increment for the first player
                REQUIRE(tLeft == tMode.toTimerString(0));
            }
        }

        WHEN("Switching to player 2")
        {
            std::thread P2Thread(&TimerMode::switchPlayer, &tMode, 1);
            P2Thread.detach();
            tMode.setStopTimer(true);

            THEN("If player 2 plays his action instantaneously, his timer should be starting time + increment")
            {
                REQUIRE(tMode.getTimeLeft(1) == startingTime + increment);
            }
        }
    }
}
