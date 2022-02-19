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

void DatabaseHandler::quickTest()
{
    // just ignore this unless you want to test the database
    // just a quick test to see if the database is working
    std::cout << "Sending test data" << std::endl;

    mongocxx::collection coll = Instance()->db[database::kCollectionName];
    auto builder = bsoncxx::builder::stream::document {};
    bsoncxx::document::value doc_value = builder << "name"
                                                 << "Test"
                                                 << "type"
                                                 << "database"
                                                 << "count" << 1 << "info" << bsoncxx::builder::stream::open_document << "x" << 203 << "y" << 102
                                                 << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view view = doc_value.view();

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(view);

    std::cout << "Data sent" << std::endl;
}

bool DatabaseHandler::createAccount(const std::string &username, const std::string &password)
{
    // check if username already exists
    if (Instance()->doesUsernameExist(username)) {
        std::cout << "Username already exists" << std::endl;
        return false;
    }
    // if not, create account
    // get user collection
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];

    // user base data
    int elo = 69;

    // create document
    auto builder = document {} << "username" << username << "password" << password << "elo" << elo << "friends" << bsoncxx::builder::stream::array()
                               << finalize;

    // insert username+password into user collection
    userColl.insert_one(builder.view());

    // return true to indicate success in creating account
    std::cout << "Account created" << std::endl;
    return true;
}

bool DatabaseHandler::doesUsernameExist(const std::string &username)
{
    // get user collection
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];

    // check if username is contained in the collection
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    if (maybeResult)
        return true;
    return false;
}

bool DatabaseHandler::checkLogin(const std::string &username, const std::string &password)
{
    // get user collection
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];

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

std::vector<std::string> DatabaseHandler::getFriends(const std::string &username)
{
    std::vector<std::string> friends;
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // if username is contained in the collection
    if (maybeResult) {
        bsoncxx::document::view view = maybeResult->view();
        auto friendsArray = view["friends"].get_array().value;
        int i = 0;
        // iterate over friends array
        while (friendsArray.find(i) != friendsArray.end()) {
            // get friend
            bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult
                = userColl.find_one(document {} << "_id" << friendsArray.find(i)->get_oid().value << finalize);
            if (maybeFriendResult) {
                // add friend name to friend vector
                bsoncxx::document::view friendView = maybeFriendResult->view();
                friends.push_back(friendView["username"].get_utf8().value.to_string());
            }
            i++;
        }
    }
    return friends;
}

void DatabaseHandler::addFriend(const std::string &username, const std::string &friendUsername)
{
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult = userColl.find_one(document {} << "username" << friendUsername << finalize);
    // check if usernames are contained in the collection
    if (maybeResult && maybeFriendResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view friendView = maybeFriendResult->view();
        bsoncxx::oid friendId = friendView["_id"].get_oid().value;
        auto friendsArray = view["friends"].get_array().value;
        int i = 0;
        // check if friend is already in friends list
        while (friendsArray.find(i) != friendsArray.end()) {
            if (friendsArray.find(i)->get_oid().value == friendId) {
                std::cout << "Friend already exists" << std::endl;
                return;
            }
            i++;
        }
        // add friend to friends list
        userColl.update_one(
            document {} << "username" << username << finalize, document {} << "$push" << open_document << "friends" << friendId << close_document << finalize);
        std::cout << "Friend added" << std::endl;
    }
}

void DatabaseHandler::removeFriend(const std::string &username, const std::string &friendUsername)
{
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult = userColl.find_one(document {} << "username" << friendUsername << finalize);
    // check if usernames are contained in the collection
    if (maybeResult && maybeFriendResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view friendView = maybeFriendResult->view();
        bsoncxx::oid friendId = friendView["_id"].get_oid().value;
        // remove friend from friends list
        userColl.update_one(
            document {} << "username" << username << finalize, document {} << "$pull" << open_document << "friends" << friendId << close_document << finalize);
        std::cout << "Friend removed" << std::endl;
    }
}

int DatabaseHandler::getELO(const std::string &username)
{
    int elo = 0;
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // if user exists
    if (maybeResult) {
        // get its elo
        bsoncxx::document::view view = maybeResult->view();
        elo = view["elo"].get_int32().value;
    }
    return elo;
}

void DatabaseHandler::setELO(const std::string &username, const int &elo)
{
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // if user exists
    if (maybeResult) {
        // set its elo
        userColl.update_one(
            document {} << "username" << username << finalize, document {} << "$set" << open_document << "elo" << elo << close_document << finalize);
    }
}