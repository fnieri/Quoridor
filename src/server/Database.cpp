//
// Created by louis on 08/02/2022.
//

#include "Database.h"

// avoids having long namespaces
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

mongocxx::instance inst {}; // Initialize MongoDB C++ driver

DatabaseHandler::DatabaseHandler()
    : uri(mongocxx::uri(database::kMongoDbUri))
    , client(mongocxx::client(uri))
    , db(client[database::kDatabaseName])
{
}

DatabaseHandler &DatabaseHandler::get()
{
    if (!singleton)
        singleton{unique_ptr<DatabaseHandler>(new DatabaseHandler())};
    return *singleton;
}

void DatabaseHandler::quickTest()
{
    // just ignore this unless you want to test the database
    // just a quick test to see if the database is working
    std::cout << "Sending test data" << std::endl;

    mongocxx::collection coll = db[database::kCollectionName];
    auto builder = bsoncxx::builder::stream::document {};
    bsoncxx::document::value doc_value = builder << "name"
                                                 << "MongoDB"
                                                 << "type"
                                                 << "database"
                                                 << "count" << 1 << "info" << bsoncxx::builder::stream::open_document << "x" << 203 << "y" << 102
                                                 << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view view = doc_value.view();

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(view);

    std::cout << "Data sent" << std::endl;
}

bool DatabaseHandler::createAccount(std::string username, std::string password)
{
    // check if username already exists
    if (doesUsernameExist(username)) {
        std::cout << "Username already exists" << std::endl;
        return false;
    }
    // if not, create account
    // get user collection
    mongocxx::collection userColl = db[database::kUserCollectionName];

    // create document
    auto builder = document {} << "username" << username << "password" << password << finalize; // still need to encrypt password. this is just a test.

    // insert username+password into user collection
    userColl.insert_one(builder.view());

    // return true to indicate success in creating account
    std::cout << "Account created" << std::endl;
    return true;
}

bool DatabaseHandler::doesUsernameExist(const std::string &username)
{
    // get user collection
    mongocxx::collection userColl = db[database::kUserCollectionName];

    // check if username is contained in the collection
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    if (maybeResult)
        return true;
    return false;
}

bool DatabaseHandler::checkLogin(std::string username, std::string password)
{
    // get user collection
    mongocxx::collection userColl = db[database::kUserCollectionName];

    // check if username is contained in the collection
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    if (maybeResult) {
        // get password from user collection
        bsoncxx::document::view view = maybeResult->view();
        std::string dbPassword = view["password"].get_utf8().value.to_string();
        // compare password
        if (password == dbPassword) {
            std::cout << "Login successful" << std::endl;
            return true;
        }
    }
    std::cout << "Login failed" << std::endl;
    return false;
}
