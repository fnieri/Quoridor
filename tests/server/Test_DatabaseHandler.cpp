//
// Created by louis on 25/02/2022.
//
#include <catch2/catch.hpp>

#include "src/server/Database.h"
#include <cstdlib>
#include <unistd.h>

SCENARIO("Creating and login into an account")
{
    GIVEN("Username and password")
    {
        DatabaseHandler::deleteAccount("testing");
        WHEN("Creating an account")
        {
            REQUIRE(DatabaseHandler::createAccount("testing", "testingPassword") == true);
        }
        WHEN("Checking credentials")
        {
            REQUIRE(DatabaseHandler::checkLogin("testing", "testingPassword") == true);
        }
    }
}