//
// Created by louis on 25/02/2022.
//
#include <catch2/catch.hpp>

#include "src/server/Database.h"
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <unistd.h>

using json = nlohmann::json;

bool isStringInVector(std::vector<std::string> vector, std::string string)
{
    for (auto &s : vector) {
        if (s == string) {
            return true;
        }
    }
    return false;
}

SCENARIO("Creating and login into an account")
{
    GIVEN("Username and password")
    {
        WHEN("Creating an account")
        {
            DatabaseHandler::deleteAccount("testing");
            DatabaseHandler::deleteAccount("testingFriend");

            REQUIRE(DatabaseHandler::createAccount("testing", "testingPassword"));
            REQUIRE(DatabaseHandler::createAccount("testingFriend", "testingFriendPassword"));
        }
        WHEN("Checking credentials")
        {
            REQUIRE(DatabaseHandler::checkLogin("testing", "testingPassword"));
            REQUIRE(DatabaseHandler::checkLogin("testingFriend", "testingFriendPassword"));
            REQUIRE(DatabaseHandler::checkLogin("testing", "wrongPassword") == false);
            REQUIRE(DatabaseHandler::checkLogin("testingFriend", "anotherWrongPassword") == false);
        }
    }
}

SCENARIO("Check ELO")
{
    GIVEN("Username and new elo")
    {
        WHEN("Getting base Elo")
        {
            REQUIRE(DatabaseHandler::getELO("testing") == 69); // change this with new default
        }

        WHEN("Set Elo")
        {
            DatabaseHandler::setELO("testing", 100);

            REQUIRE(DatabaseHandler::getELO("testing") == 100);
        }
    }
}

SCENARIO("Handling friends")
{
    GIVEN("Username and friend username")
    {
        WHEN("Checking sent friend requests")
        {
            DatabaseHandler::sendFriendRequest("testing", "testingFriend");

            REQUIRE(isStringInVector(DatabaseHandler::getSentFriendRequests("testing"), "testingFriend"));
            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getSentFriendRequests("testingFriend"), "testing"));
        }

        WHEN("Checking received friend requests")
        {
            REQUIRE(isStringInVector(DatabaseHandler::getReceivedFriendRequests("testingFriend"), "testing"));
            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getReceivedFriendRequests("testing"), "testingFriend"));
        }

        WHEN("Accepting friend request")
        {
            DatabaseHandler::acceptFriendRequest("testing", "testingFriend");

            REQUIRE(isStringInVector(DatabaseHandler::getFriends("testingFriend"), "testing"));
            REQUIRE(isStringInVector(DatabaseHandler::getFriends("testing"), "testingFriend"));
        }

        WHEN("Removing a friend")
        {
            DatabaseHandler::removeFriend("testing", "testingFriend");

            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getFriends("testingFriend"), "testing"));
            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getFriends("testing"), "testingFriend"));
        }

        WHEN("Refusing a friend request")
        {
            DatabaseHandler::sendFriendRequest("testing", "testingFriend");
            DatabaseHandler::removeFriendRequest("testing", "testingFriend");

            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getReceivedFriendRequests("testingFriend"), "testing"));
            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getSentFriendRequests("testingFriend"), "testing"));
            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getReceivedFriendRequests("testing"), "testingFriend"));
            REQUIRE_FALSE(isStringInVector(DatabaseHandler::getSentFriendRequests("testing"), "testingFriend"));
        }
    }
}

SCENARIO("Chatting between friends")
{
    GIVEN("Username and game id")
    {
        WHEN("Recording a message")
        {
            DatabaseHandler::sendFriendRequest("testing", "testingFriend");
            DatabaseHandler::acceptFriendRequest("testing", "testingFriend");

            DatabaseHandler::recordMessage("testingFriend", "testing", "testingMessage");

            std::vector<std::vector<std::string>> userAMessages = DatabaseHandler::getMessages("testing", "testingFriend");
            std::vector<std::vector<std::string>> userBMessages = DatabaseHandler::getMessages("testingFriend", "testing");

            REQUIRE(userAMessages[userAMessages.size() - 1][0] == "testingFriend");
            REQUIRE(userBMessages[userBMessages.size() - 1][1] == "testingMessage");

            DatabaseHandler::recordMessage("testing", "testingFriend", "another message 123");

            std::vector<std::vector<std::string>> userAMessages1 = DatabaseHandler::getMessages("testing", "testingFriend");
            std::vector<std::vector<std::string>> userBMessages1 = DatabaseHandler::getMessages("testingFriend", "testing");

            REQUIRE(userAMessages1[userAMessages1.size() - 1][0] == "testing");
            REQUIRE(userBMessages1[userBMessages1.size() - 1][1] == "another message 123");
        }
    }
}

SCENARIO("Handling game config")
{
    GIVEN("Game Id")
    {
        json boardConfig = {{"players_position", {{{"x", 1}, {"y", 0}}, {{"x", 7}, {"y", 8}}}},
            {"wall_position", {{{"x", 4}, {"y", 6}}, {{"x", 2}, {"y", 1}}, {{"x", 5}, {"y", 2}}}}, {"leftover_walls", {7, 4}}};

        json gameConfig = {{"game_id", 69}, {"player_number", 2}, {"players_username", {"testing", "testingFriend"}}, {"board_config", boardConfig}};

        WHEN("CREATING A GAME")
        {
            DatabaseHandler::deleteGame(69);

            DatabaseHandler::createGame(69, {"testing", "testingFriend"}, 2, boardConfig);

            std::cout << DatabaseHandler::getGameConfig(69) << std::endl;

            std::cout << DatabaseHandler::getGameBoardConfig(69) << std::endl;

            DatabaseHandler::addGameIdToUser("testing", 69);

            DatabaseHandler::addGameIdInviteToUser("testingFriend", 69);

            REQUIRE(DatabaseHandler::getPlayerGameIds("testing") == std::vector<int>({69}));

            REQUIRE(DatabaseHandler::getPlayerInviteGameIds("testingFriend") == std::vector<int>({69}));

            REQUIRE_FALSE(DatabaseHandler::getPlayerInviteGameIds("testing") == std::vector<int>({69}));

            REQUIRE_FALSE(DatabaseHandler::getPlayerGameIds("testingFriend") == std::vector<int>({69}));
        }

        WHEN("UPDATING A GAME")
        {
            json newBoardConfig = {{"players_position", {{{"x", 1}, {"y", 0}}, {{"x", 7}, {"y", 8}}}},
                {"wall_position", {{{"x", 5}, {"y", 6}}, {{"x", 2}, {"y", 1}}, {{"x", 5}, {"y", 2}}}}, {"leftover_walls", {6, 2}}};

            DatabaseHandler::setGameBoardConfig(69, newBoardConfig);

            std::cout << DatabaseHandler::getGameConfig(69) << std::endl;

            std::cout << DatabaseHandler::getGameBoardConfig(69) << std::endl;

            REQUIRE(DatabaseHandler::getGameBoardConfig(69) == newBoardConfig);

            REQUIRE_FALSE(DatabaseHandler::getGameBoardConfig(69) == boardConfig);
        }

        WHEN("DELETING A GAME")
        {
            DatabaseHandler::deleteGame(69);

            REQUIRE_FALSE(DatabaseHandler::isGameIdUsed(69));

            REQUIRE_FALSE(DatabaseHandler::getPlayerInviteGameIds("testing") == std::vector<int>({69}));

            REQUIRE_FALSE(DatabaseHandler::getPlayerInviteGameIds("testingFriend") == std::vector<int>({69}));

            REQUIRE_FALSE(DatabaseHandler::getPlayerGameIds("testing") == std::vector<int>({69}));

            REQUIRE_FALSE(DatabaseHandler::getPlayerGameIds("testingFriend") == std::vector<int>({69}));
        }
    }
}

SCENARIO("Handling game chat")
{
    GIVEN("Username and game id")
    {
        WHEN("Checking games")
        {
            DatabaseHandler::recordMessage("testing", "Game chat test message", 69);

            std::vector<std::vector<std::string>> gameChatMessages = DatabaseHandler::getMessages(69);

            REQUIRE(gameChatMessages[gameChatMessages.size() - 1][0] == "testing");
            REQUIRE(gameChatMessages[gameChatMessages.size() - 1][1] == "Game chat test message");
        }
    }
}
