//
// Created by louis on 08/02/2022.
//
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
// this will need to be changed to env variables
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
    static bool createAccount(const std::string &username, const std::string &password);
    static bool checkLogin(const std::string &username, const std::string &password);

    // TODO
    static std::vector<std::string> getFriends(const std::string &username);
    static void addFriend(const std::string &username, const std::string &friendUsername);
    static void removeFriend(const std::string &username, const std::string &friendUsername);
    static int getELO(const std::string &username);
    static void setELO(const std::string &username, const int &elo);
};