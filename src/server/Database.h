//
// Created by louis on 08/02/2022.
//
/**
 * @file Database.h
 * @brief Database handler to interact with the database.
 * @author Louis Vanstappen
 * @date 18/02/2022
 * @details This class handles any database related operations, such as creating accounts and storing game related data.
 */
#pragma once

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include <cstdint>
#include <iostream>

namespace database
{
const char kUsername[] {"louis"};
constexpr char kPassword[] {"randompass456"};
// need to actually use username and password
constexpr char kMongoDbUri[] {"mongodb+srv://louis:randompass456@quoridor.fbwoc.mongodb.net/myFirstDatabase?retryWrites=true&w=majority"};
constexpr char kDatabaseName[] {"testing"};
constexpr char kCollectionName[] {"TestCollection"};
constexpr char kUserCollectionName[] {"UserCollection"};
}

class DatabaseHandler
{
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
    /**
     * @brief Check whether or not a user with the given username exists.
     * @param username string.
     * @return Returns true if the user exists, false otherwise.
     */
    static bool doesUsernameExist(const std::string &username);
    DatabaseHandler();
    static std::unique_ptr<DatabaseHandler> &Instance()
    {
        static std::unique_ptr<DatabaseHandler> singleton;
        if (!singleton)
            singleton = std::move(std::unique_ptr<DatabaseHandler> {new DatabaseHandler});
        return singleton;
    }

public:
    static void quickTest();
    /**
     * @brief Create an account with the given username and password. Encrypts the password and stores salt key.
     * @param username and raw password string.
     * @return Returns true if the account was successfully created, false otherwise.
     */
    static bool createAccount(const std::string &username, const std::string &password);
    /**
     * @brief Check whether or not the given username and password are valid.
     * @param username and raw password string
     * @return True if the credentials are correct, false otherwise.
     */
    static bool checkLogin(const std::string &username, const std::string &password);
    /**
     * @brief Delete the account with the given username.
     * @param username string.
     * @warning This action is irreversible.
     * @note In theory this function is just used for testing purposes. (at least for now)
     */
    static void deleteAccount(const std::string &username);
    /**
     * @brief Get the list of friends of the given username.
     * @param username string.
     * @return User's friends username string vector.
     */
    static std::vector<std::string> getFriends(const std::string &username);
    /**
     * @brief Get the list of sent friend requests of the given username.
     * @param username string.
     * @return User's sent friend requests username string vector.
     */
    static std::vector<std::string> getSentFriendRequests(const std::string &username);
    /**
     * @brief Get the list of received friend requests of the given username.
     * @param username string.
     * @return User's received friend requests username string vector.
     */
    static std::vector<std::string> getReceivedFriendRequests(const std::string &username);
    /**
     * @brief Add a friend to the given username's friend list.
     * @param username string.
     * @warning Do not use in implementation.
     * @note No real need to use this. It's just for testing purposes.
     */
    static void addFriend(const std::string &username, const std::string &friendUsername);
    /**
     * @brief Remove a friend from the given username's friend list.
     * @param username string.
     */
    static void removeFriend(const std::string &username, const std::string &friendUsername);
    /**
     * @brief Send a friend request to the given username.
     * @param username string.
     */
    static void sendFriendRequest(const std::string &sender, const std::string &receiver);
    /**
     * @brief Remove a friend request sent to the given receiver from the given sender.
     * @param sender username string, receiver username string.
     */
    static void removeFriendRequest(const std::string &receiver, const std::string &sender);
    /**
     * @brief Accept a friend request received from the given sender to the given receiver.
     * @param receiver username string, sender username string.
     */
    static void acceptFriendRequest(const std::string &receiver, const std::string &sender);
    /**
     * @brief Get a user's elo rating.
     * @param username string.
     * @return User's elo rating as int.
     */
    static int getELO(const std::string &username);
    /**
     * @brief Set a user's elo rating.
     * @param username string.
     * @warning Use with caution if using threads. Ideally use a mutex to avoid double-writing of the elo. Double-writing won't make the Database crash, it's
     * just not a good idea.
     */
    static void setELO(const std::string &username, const int &elo);

    // TODO
    static void sendMessage(const std::string &sender, const std::string &receiver, const std::string &message);
    static std::vector<std::vector<std::string>> getMessages(const std::string &username);
};