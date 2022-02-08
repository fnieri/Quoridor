//
// Created by louis on 08/02/2022.
//

#include "Database.h"

mongocxx::instance inst {}; // Initialize MongoDB C++ driver

DatabaseHandler::DatabaseHandler()
    : uri(mongocxx::uri(database::kMongoDbUri))
    , client(mongocxx::client(uri))
    , db(client[database::kDatabaseName])
{
}

void DatabaseHandler::quickTest()
{
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
