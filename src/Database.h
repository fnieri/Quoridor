//
// Created by louis on 08/02/2022.
//

#ifndef QUORIDOR_DATABASE_H
#define QUORIDOR_DATABASE_H
#pragma once

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include <cstdint>
#include <iostream>

// avoids having long namespaces
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

namespace database
{
// this will need to be changed to env variables
const char kUsername[] = "louis";
constexpr char kPassword[] = "randompass456";
// need to actually use username and password
constexpr char kMongoDbUri[] = "mongodb+srv://louis:randompass456@quoridor.fbwoc.mongodb.net/myFirstDatabase?retryWrites=true&w=majority";
constexpr char kDatabaseName[] = "testing";
constexpr char kCollectionName[] = "TestCollection";
constexpr char kUserCollectionName[] = "UserCollection";
}

class DatabaseHandler
{
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
    bool doesUsernameExist(const std::string &username);
public:
    DatabaseHandler();
    void quickTest();
    bool createAccount(std::string username, std::string password);
    bool checkLogin(std::string username, std::string password);

    // TODO
//    void getFriends(std::string username); should be json
    void addFriend(std::string username, std::string friendUsername);
    void removeFriend(std::string username, std::string friendUsername);
};

#endif // QUORIDOR_DATABASE_H
