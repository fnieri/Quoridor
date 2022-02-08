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

namespace database
{
// this will need to be changed to env variables
const char kUsername[] = "louis";
constexpr char kPassword[] = "randompass456";
// need to actually use username and password
constexpr char kMongoDbUri[] = "mongodb+srv://louis:randompass456@quoridor.fbwoc.mongodb.net/myFirstDatabase?retryWrites=true&w=majority";
constexpr char kDatabaseName[] = "testing";
constexpr char kCollectionName[] = "TestCollection";
}

class DatabaseHandler
{
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
public:
    DatabaseHandler();
    void quickTest();
};

#endif // QUORIDOR_DATABASE_H
