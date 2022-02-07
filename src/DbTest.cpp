//
// Created by louis on 07/02/2022.
//

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/json.hpp>
#include <cstdint>
#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <vector>
//...
int main()
{
    printf("Hello, World!\n");
    mongocxx::instance inst {};
    const auto uri = mongocxx::uri {"mongodb+srv://louis:randompass456@quoridor.fbwoc.mongodb.net/myFirstDatabase?retryWrites=true&w=majority"};
    mongocxx::client conn {uri};
    mongocxx::database db = conn["test"];

    mongocxx::collection coll = db["okok"];

    auto builder = bsoncxx::builder::stream::document {};
    bsoncxx::document::value doc_value = builder << "name"
                                                 << "MongoDB"
                                                 << "type"
                                                 << "database"
                                                 << "count" << 1 << "info" << bsoncxx::builder::stream::open_document << "x" << 203 << "y" << 102
                                                 << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view view = doc_value.view();

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(view);

    return 0;
}
