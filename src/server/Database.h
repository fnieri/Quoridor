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

#include "Config.h"
#include "ConfigEnums.h"

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <nlohmann/json_fwd.hpp>

#include <cstdint>
#include <iostream>
#include <mutex>

using json = nlohmann::json;

namespace database
{
//// need to actually use username and password
//// constexpr char kMongoDbUri[] {"mongodb+srv://louis:randompass456@quoridor.fbwoc.mongodb.net/myFirstDatabase?retryWrites=true&w=majority"};
//constexpr char kMongoDbUri[] {"mongodb://quoridor:ulb123@46.101.255.42:47984"};
////constexpr char kMongoDbUri[] {"mongodb://quoridor:ulb123@localhost:47984"};

const std::string kMongoDbUri = ConfigHandler::Instance()->getServerProperty(ServerProperty::DB_ADDRESS);
constexpr char kDatabaseName[] {"testing"};
constexpr char kCollectionName[] {"TestCollection"};
constexpr char kUserCollectionName[] {"UserCollection"};
constexpr char kChatCollectionName[] {"ChatCollection"};
constexpr char kGameCollectionName[] {"GameCollection"};
}

class DatabaseHandler
{
    static std::mutex m_dbMutex;

    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
    /**
     * @brief Check whether or not a user with the given username exists.
     * @param username string.
     * @return True if the user exists, false otherwise.
     */
    static auto doesUsernameExist(const std::string &username) -> bool;
    static auto getChatId(bsoncxx::oid senderId, bsoncxx::oid receiverId) -> std::string;

    DatabaseHandler();
    static std::unique_ptr<DatabaseHandler> &Instance()
    {
        static std::unique_ptr<DatabaseHandler> singleton;
        if (!singleton)
            singleton = std::move(std::unique_ptr<DatabaseHandler> {new DatabaseHandler});
        return singleton;
    }

public:
    static auto quickTest() -> void;
    /**
     * @brief Create an account with the given username and password. Encrypts the password and stores salt key.
     * @param username and raw password string.
     * @return True if the account was successfully created, false otherwise.
     */
    static auto createAccount(const std::string &username, const std::string &password) -> bool;
    /**
     * @brief Check whether or not the given username and password are valid.
     * @param username and raw password string
     * @return True if the credentials are correct, false otherwise.
     */
    static auto checkLogin(const std::string &username, const std::string &password) -> bool;
    /**
     * @brief Delete the account with the given username.
     * @param username string.
     * @warning This action is irreversible.
     * @note In theory this function is just used for testing purposes. (at least for now)
     */
    static auto deleteAccount(const std::string &username) -> void;
    /**
     * @brief Get the list of friends of the given username.
     * @param username string.
     * @return User's friends username string vector.
     */
    static auto getFriends(const std::string &username) -> std::vector<std::string>;
    /**
     * @brief Get the list of sent friend requests of the given username.
     * @param username string.
     * @return User's sent friend requests username string vector.
     */
    static auto getSentFriendRequests(const std::string &username) -> std::vector<std::string>;
    /**
     * @brief Get the list of received friend requests of the given username.
     * @param username string.
     * @return User's received friend requests username string vector.
     */
    static auto getReceivedFriendRequests(const std::string &username) -> std::vector<std::string>;
    /**
     * @brief Add a friend to the given username's friend list.
     * @param username string.
     * @warning Do not use in implementation.
     * @note No real need to use this. It's just for testing purposes.
     */
    static auto addFriend(const std::string &username, const std::string &friendUsername) -> void;
    /**
     * @brief Remove a friend from the given username's friend list.
     * @param username string.
     */
    static auto removeFriend(const std::string &username, const std::string &friendUsername) -> void;
    /**
     * @brief Send a friend request to the given username.
     * @param username string.
     */
    static auto sendFriendRequest(const std::string &friendRequestSender, const std::string &friendRequestReceiver) -> void;
    /**
     * @brief Remove a friend request sent to the given receiver from the given sender.
     * @param sender username string, receiver username string.
     */
    static auto removeFriendRequest(const std::string &friendRequestReceiver, const std::string &friendRequestSender) -> void;
    /**
     * @brief Accept a friend request received from the given sender to the given receiver.
     * @param receiver username string, sender username string.
     */
    static auto acceptFriendRequest(const std::string &friendRequestSender, const std::string &friendRequestReceiver) -> void;
    /**
     * @brief Get a user's elo rating.
     * @param username string.
     * @return User's elo rating as int.
     */
    static auto getELO(const std::string &username) -> int;
    /**
     * @brief Set a user's elo rating.
     * @param username string.
     * @warning Use with caution if using threads. Ideally use a mutex to avoid double-writing of the elo. Double-writing won't make the Database crash, it's
     * just not a good idea.
     */
    static auto setELO(const std::string &username, const int &elo) -> void;
    /**
     * @brief Send a message from a user to another user
     * @param sender username string, receiver username string, message string.
     */
    static auto recordMessage(const std::string &sender, const std::string &receiver, const std::string &message) -> void;
    /**
     * @brief Send a message from a user in a game chat.
     * @param sender username string, message string, game id int.
     */
    static auto recordMessage(const std::string &sender, const std::string &message, const int &gameId) -> void;
    /**
     * @brief Get a user's messages with another user.
     * @param username string, friend username string.
     * @note The order in which the username parameters are passed is not important. (user1, user2) and (user2, user1) will return the same thing.
     * @return Vector of vector of strings. The first string is the sender username, the second string is the sender message.
     */
    static auto getMessages(const std::string &username, const std::string &friendUsername) -> std::vector<std::vector<std::string>>;
    /**
     * @brief Get a the messages sent in a game chat.
     * @param game id int.
     * @return Vector of vector of strings. The first string is the sender username, the second string is the sender message.
     */
    static auto getMessages(const int &gameId) -> std::vector<std::vector<std::string>>;
    /**
     * @brief Check whether or not a gameId is already used.
     * @param game id int.
     * @return True if the game id is already used, false otherwise.
     */
    static auto isGameIdUsed(const int &gameId) -> bool;

    /**
     * @brief Add game id to the user's list of accepted games and delete it from the user's gameId invite list.
     * @param username string, gameId int.
     * @note if you call this and the gameId is not in the user's invite list, it will not throw an error.
     */
    static auto addGameIdToUser(const std::string &username, const int &gameId) -> void;

    /**
     * @brief Add game id to the user's list of invited games.
     * @param string username, int gameId.
     */
    static auto addGameIdInviteToUser(const std::string &username, const int &gameId) -> void;

    /**
     * @brief Create a new game.
     * @param int gameId, vector<str> players, int number_of_players, json boardConfig
     * @warning The gameId must be unique and no verification is made. Use isGameIdUsed() to check if the gameId is already used before creating a game.
     */
    static auto createGame(const int &gameId, const std::vector<std::string> &players, const int &nPlayers, const json &boardConfig) -> void;

    /**
     * @brief Get the board configuration of a game.
     * @param int gameId
     * @return json boardConfig of the game.
     */
    static auto getGameBoardConfig(const int &gameId) -> json;

    /**
     * @brief Get the game configuration of a game.
     * @param int gameId
     * @return json gameConfig of the game.
     */
    static auto getGameConfig(const int &gameId) -> json;

    /**
     * @brief Get the player's accepted gameIds.
     * @param string username
     * @return vector<int> player's accepted gameIds.
     */
    static auto getPlayerGameIds(const std::string &username) -> std::vector<int>;

    /**
     * @brief remove game id to the user's list
     * @param username string, gameId int.
     * @note if you call this and the gameId is not in the user's invite list, it will not throw an error.
     */
    static auto removeGameIdFromUser(const std::string &username, const int &gameId) -> void;

    /**
     * @brief Get the player's invited gameIds.
     * @param string username
     * @return vector<int> player's invited gameIds.
     */
    static auto getPlayerInviteGameIds(const std::string &username) -> std::vector<int>;

    /**
     * @brief Set the board config of a game.
     * @param int gameId, json boardConfig
     */
    static auto setGameBoardConfig(const int &gameId, const json &boardConfig) -> void;

    /**
     * @brief Delete a game.
     * @param int gameId
     * @warning This action is irreversible.
     * @note This method will also handle the deletion of the gameId appearance in all user's accepted and invited gameIds.
     */
    static auto deleteGame(const int &gameId) -> void;

    /**
     * @brief Get the leaderboard with the n best players.
     * @param int nPlayers
     * @return json leaderboard with username and elo.
     */
    static auto getLeaderboard(const int &nPlayers) -> json;
};
