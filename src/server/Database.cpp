//
// Created by louis on 08/02/2022.
//

#include "Database.h"

#include "PasswordEncrypter.h"

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

std::mutex DatabaseHandler::m_dbMutex;

void DatabaseHandler::quickTest()
{
    static std::lock_guard<std::mutex> guard {m_dbMutex};

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
    std::lock_guard<std::mutex> guard {m_dbMutex};

    // check if username already exists
    if (Instance()->doesUsernameExist(username)) {
        return false;
    }
    // if not, create account
    // get user collection
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];

    // user base data
    int elo = 69;

    std::vector<std::string> encryption = PasswordEncrypter::registerEncryption(password);
    std::string saltKey = encryption[0];
    std::string encryptedPassword = encryption[1];

    // create document
    auto builder = document {} << "username" << username << "password" << encryptedPassword << "salt_key" << saltKey << "elo" << elo << "friends"
                               << bsoncxx::builder::stream::array() << "sentFriendRequests" << bsoncxx::builder::stream::array() << "receivedFriendRequests"
                               << bsoncxx::builder::stream::array() << "invite_gameId" << bsoncxx::builder::stream::array() << "accepted_gameId"
                               << bsoncxx::builder::stream::array() << finalize;

    // insert username+password into user collection
    userColl.insert_one(builder.view());

    // return true to indicate success in creating account
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
    std::lock_guard<std::mutex> guard {m_dbMutex};

    // get user collection
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];

    // check if username is contained in the collection
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    if (maybeResult) {
        // get password from user collection
        bsoncxx::document::view view = maybeResult->view();
        std::string dbPassword = view["password"].get_string().value.to_string();
        std::string saltKey = view["salt_key"].get_string().value.to_string();

        // compare password
        if (PasswordEncrypter::compareHash(password, saltKey, dbPassword)) {
            return true;
        }
    }
    return false;
}

void DatabaseHandler::deleteAccount(const std::string &username)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    // get user collection
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];

    // delete username from user collection
    userColl.delete_one(document {} << "username" << username << finalize);
}

std::vector<std::string> DatabaseHandler::getFriends(const std::string &username)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

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
                friends.push_back(friendView["username"].get_string().value.to_string());
            }
            i++;
        }
    }



    return friends;
}

std::vector<std::string> DatabaseHandler::getSentFriendRequests(const std::string &username)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    std::vector<std::string> sentFriendRequests;
    if (maybeResult) {
        bsoncxx::document::view view = maybeResult->view();
        auto sentFriendRequestsArray = view["sentFriendRequests"].get_array().value;
        int i = 0;
        // get all sent friend requests
        while (sentFriendRequestsArray.find(i) != sentFriendRequestsArray.end()) {
            bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult
                = userColl.find_one(document {} << "_id" << sentFriendRequestsArray.find(i)->get_oid().value << finalize);
            if (maybeFriendResult) {
                // add friend name to friend vector
                bsoncxx::document::view friendView = maybeFriendResult->view();
                sentFriendRequests.push_back(friendView["username"].get_string().value.to_string());
            }
            i++;
        }
    }
    return sentFriendRequests;
}

std::vector<std::string> DatabaseHandler::getReceivedFriendRequests(const std::string &username)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    std::vector<std::string> receivedFriendRequests;
    if (maybeResult) {
        bsoncxx::document::view view = maybeResult->view();
        auto receivedFriendRequestsArray = view["receivedFriendRequests"].get_array().value;
        int i = 0;
        // get all received friend requests
        while (receivedFriendRequestsArray.find(i) != receivedFriendRequestsArray.end()) {
            bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult
                = userColl.find_one(document {} << "_id" << receivedFriendRequestsArray.find(i)->get_oid().value << finalize);
            if (maybeFriendResult) {
                // add friend name to friend vector
                bsoncxx::document::view friendView = maybeFriendResult->view();
                receivedFriendRequests.push_back(friendView["username"].get_string().value.to_string());
            }
            i++;
        }
    }
    return receivedFriendRequests;
}

// TODO : may cause issues with threads
void DatabaseHandler::acceptFriendRequest(const std::string &friendRequestSender, const std::string &friendRequestReceiver)
{
    // verification just in case but this should not be necessary if everything is implemented correctly
    std::vector<std::string> sentFriendRequests = getSentFriendRequests(friendRequestSender);
    std::vector<std::string> receivedFriendRequests = getReceivedFriendRequests(friendRequestReceiver);

    std::lock_guard<std::mutex> guard {m_dbMutex};

    bool valid = false;
    for (auto &sentFriendRequest : sentFriendRequests) {
        if (sentFriendRequest == friendRequestReceiver) {
            for (auto &receivedFriendRequest : receivedFriendRequests) {
                if (receivedFriendRequest == friendRequestSender) {
                    valid = true;
                    break;
                }
            }
            break;
        }
    }
    if (!valid)
        return;

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << friendRequestSender << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeReceiverResult = userColl.find_one(document {} << "username" << friendRequestReceiver << finalize);
    if (maybeResult && maybeReceiverResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view friendRequestReceiverView = maybeReceiverResult->view();
        bsoncxx::oid friendRequestSenderId = view["_id"].get_oid().value;
        bsoncxx::oid friendRequestReceiverId = friendRequestReceiverView["_id"].get_oid().value;

        // remove receiver from sent friend requests
        userColl.update_one(document {} << "username" << friendRequestSender << finalize,
            document {} << "$pull" << open_document << "sentFriendRequests" << friendRequestReceiverId << close_document << finalize);
        // remove sender from received friend requests
        userColl.update_one(document {} << "username" << friendRequestReceiver << finalize,
            document {} << "$pull" << open_document << "receivedFriendRequests" << friendRequestSenderId << close_document << finalize);
        // add receiver to user's friends
        userColl.update_one(document {} << "username" << friendRequestSender << finalize,
            document {} << "$push" << open_document << "friends" << friendRequestReceiverId << close_document << finalize);
        // add sender to receiver's friends
        userColl.update_one(document {} << "username" << friendRequestReceiver << finalize,
            document {} << "$push" << open_document << "friends" << friendRequestSenderId << close_document << finalize);
    }
}

void DatabaseHandler::removeFriendRequest(const std::string &friendRequestSender, const std::string &friendRequestReceiver)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    // no need for verification bc if request doesn't exist, nothing will happen
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << friendRequestSender << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeReceiverResult = userColl.find_one(document {} << "username" << friendRequestReceiver << finalize);
    if (maybeResult && maybeReceiverResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view friendRequestReceiverView = maybeReceiverResult->view();
        bsoncxx::oid friendRequestSenderId = view["_id"].get_oid().value;
        bsoncxx::oid friendRequestReceiverId = friendRequestReceiverView["_id"].get_oid().value;

        // remove receiver from sent friend requests
        userColl.update_one(document {} << "username" << friendRequestSender << finalize,
            document {} << "$pull" << open_document << "sentFriendRequests" << friendRequestReceiverId << close_document << finalize);
        // remove sender from received friend requests
        userColl.update_one(document {} << "username" << friendRequestReceiver << finalize,
            document {} << "$pull" << open_document << "receivedFriendRequests" << friendRequestSenderId << close_document << finalize);
    }
}

void DatabaseHandler::addFriend(const std::string &username, const std::string &friendUsername)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    // wont be used since friends are added automatically when friend request is accepted
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
                return;
            }
            i++;
        }
        // add friend to friends list
        userColl.update_one(
            document {} << "username" << username << finalize, document {} << "$push" << open_document << "friends" << friendId << close_document << finalize);
    }
}

void DatabaseHandler::removeFriend(const std::string &username, const std::string &friendUsername)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult = userColl.find_one(document {} << "username" << friendUsername << finalize);
    // check if usernames are contained in the collection
    if (maybeResult && maybeFriendResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view friendView = maybeFriendResult->view();
        bsoncxx::oid id = view["_id"].get_oid().value;
        bsoncxx::oid friendId = friendView["_id"].get_oid().value;
        // remove friend from friends list
        userColl.update_one(
            document {} << "username" << username << finalize, document {} << "$pull" << open_document << "friends" << friendId << close_document << finalize);
        userColl.update_one(
            document {} << "username" << friendUsername << finalize, document {} << "$pull" << open_document << "friends" << id << close_document << finalize);
    }
}

// TODO : may cause issues with threads
void DatabaseHandler::sendFriendRequest(const std::string &friendRequestSender, const std::string &friendRequestReceiver)
{

    // check that they are not already friends. this verification should not be necessary if everything is implemented correctly
    std::vector<std::string> senderFriends = getFriends(friendRequestSender);
    std::vector<std::string> receiverFriends = getFriends(friendRequestReceiver);

    std::lock_guard<std::mutex> guard {m_dbMutex};

    for (auto &sentFriendRequest : senderFriends) {
        if (sentFriendRequest == friendRequestReceiver) {
            for (auto &receivedFriendRequest : receiverFriends) {
                if (receivedFriendRequest == friendRequestSender)
                    return;
            }
            return;
        }
    }

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << friendRequestSender << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult = userColl.find_one(document {} << "username" << friendRequestReceiver << finalize);
    // check if usernames are contained in the collection
    if (maybeResult && maybeFriendResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view friendView = maybeFriendResult->view();
        bsoncxx::oid senderId = view["_id"].get_oid().value;
        bsoncxx::oid friendId = friendView["_id"].get_oid().value;
        auto sentFriendRequestsArray = view["sentFriendRequests"].get_array().value;
        int i = 0;
        // check if friend is already in friends request array
        while (sentFriendRequestsArray.find(i) != sentFriendRequestsArray.end()) {
            if (sentFriendRequestsArray.find(i)->get_oid().value == friendId) {
                return;
            }
            i++;
        }
        // add friend to friend requests list
        userColl.update_one(document {} << "username" << friendRequestSender << finalize,
            document {} << "$push" << open_document << "sentFriendRequests" << friendId << close_document << finalize);
        // add friend request to friend's received friend requests list
        userColl.update_one(document {} << "username" << friendRequestReceiver << finalize,
            document {} << "$push" << open_document << "receivedFriendRequests" << senderId << close_document << finalize);
    }
}

int DatabaseHandler::getELO(const std::string &username)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

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
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // if user exists
    if (maybeResult) {
        // set its elo
        userColl.update_one(
            document {} << "username" << username << finalize, document {} << "$set" << open_document << "elo" << elo << close_document << finalize);
    }
}

std::string DatabaseHandler::getChatId(bsoncxx::oid senderId, bsoncxx::oid receiverId)
{
    std::string idStr1, idStr2;
    if (senderId < receiverId) {
        idStr1 = senderId.to_string();
        idStr2 = receiverId.to_string();
    } else {
        idStr1 = receiverId.to_string();
        idStr2 = senderId.to_string();
    }
    std::string chatId = idStr1 + idStr2;
    return chatId;
}

void DatabaseHandler::recordMessage(const std::string &sender, const std::string &receiver, const std::string &message)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << sender << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult = userColl.find_one(document {} << "username" << receiver << finalize);
    // check if usernames are contained in the collection
    if (maybeResult && maybeFriendResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view receiverView = maybeFriendResult->view();
        bsoncxx::oid senderId = view["_id"].get_oid().value;
        bsoncxx::oid receiverId = receiverView["_id"].get_oid().value;
        std::string chatId = getChatId(senderId, receiverId);
        mongocxx::collection chatColl = Instance()->db[database::kChatCollectionName];

        if (!chatColl.find_one(document {} << "chat_id" << chatId << finalize)) {
            chatColl.insert_one(document {} << "chat_id" << chatId << finalize);
        }
        chatColl.update_one(document {} << "chat_id" << chatId << finalize,
            document {} << "$push" << open_document << "messages" << open_document << sender << message << close_document << close_document << finalize);
    }
}

std::vector<std::vector<std::string>> DatabaseHandler::getMessages(const std::string &username, const std::string &friendUsername)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    std::vector<std::vector<std::string>> messages;
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeFriendResult = userColl.find_one(document {} << "username" << friendUsername << finalize);
    // check if usernames are contained in the collection
    if (maybeResult && maybeFriendResult) {
        bsoncxx::document::view view = maybeResult->view();
        bsoncxx::document::view friendView = maybeFriendResult->view();
        bsoncxx::oid senderId = view["_id"].get_oid().value;
        bsoncxx::oid friendId = friendView["_id"].get_oid().value;
        std::string chatId = getChatId(senderId, friendId);
        mongocxx::collection chatColl = Instance()->db[database::kChatCollectionName];
        bsoncxx::stdx::optional<bsoncxx::document::value> chat = chatColl.find_one(document {} << "chat_id" << chatId << finalize);

        if (chat) {
            bsoncxx::document::view chatView = chat->view();
            auto messagesArray = chatView["messages"].get_array().value;
            int i = 0;
            // get all received friend requests
            while (messagesArray.find(i) != messagesArray.end()) {
                bsoncxx::document::view messageView = messagesArray.find(i)->get_document().view();
                auto messageJson = json::parse(bsoncxx::to_json(messageView));
                for (auto &element : messageJson.items()) {
                    std::vector<std::string> message;
                    message.push_back(element.key());
                    message.push_back(element.value().get<std::string>());
                    messages.push_back(message);
                }

                i++;
            }
        }
    }
    return messages;
}

void DatabaseHandler::recordMessage(const std::string &sender, const std::string &message, const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << sender << finalize);
    // check if usernames are contained in the collection
    if (maybeResult) {
        mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];

        if (!gameColl.find_one(document {} << "game_id" << gameId << finalize)) {
            gameColl.insert_one(document {} << "game_id" << gameId << finalize);
        }
        gameColl.update_one(document {} << "game_id" << gameId << finalize,
            document {} << "$push" << open_document << "messages" << open_document << sender << message << close_document << close_document << finalize);
    }
}

std::vector<std::vector<std::string>> DatabaseHandler::getMessages(const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    std::vector<std::vector<std::string>> messages;
    mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = gameColl.find_one(document {} << "game_id" << gameId << finalize);
    // check if gameId is contained in the collection
    if (maybeResult) {
        auto gameView = maybeResult->view();
        auto messagesArray = gameView["messages"].get_array().value;
        int i = 0;
        // get all received friend requests
        while (messagesArray.find(i) != messagesArray.end()) {
            bsoncxx::document::view messageView = messagesArray.find(i)->get_document().view();
            auto messageJson = json::parse(bsoncxx::to_json(messageView));
            for (auto &element : messageJson.items()) {
                std::vector<std::string> message;
                message.push_back(element.key());
                message.push_back(element.value().get<std::string>());
                messages.push_back(message);
            }
            i++;
        }
    }
    return messages;
}

void DatabaseHandler::addGameIdToUser(const std::string &username, const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // check if usernames are contained in the collection
    if (maybeResult) {
        userColl.update_one(document {} << "username" << username << finalize,
            document {} << "$push" << open_document << "accepted_gameId" << gameId << close_document << finalize);
        userColl.update_one(document {} << "username" << username << finalize,
            document {} << "$pull" << open_document << "invite_gameId" << gameId << close_document << finalize);
    }
}

void DatabaseHandler::addGameIdInviteToUser(const std::string &username, const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // check if usernames are contained in the collection
    if (maybeResult) {
        userColl.update_one(document {} << "username" << username << finalize,
            document {} << "$push" << open_document << "invite_gameId" << gameId << close_document << finalize);
    }
}

void DatabaseHandler::removeGameIdFromUser(const std::string &username, const int &gameId)
{
    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // check if usernames are contained in the collection
    if (maybeResult) {
        userColl.update_one(document {} << "username" << username << finalize,
            document {} << "$pull" << open_document << "accepted_gameId" << gameId << close_document << finalize);
        userColl.update_one(document {} << "username" << username << finalize,
            document {} << "$pull" << open_document << "invite_gameId" << gameId << close_document << finalize);
    }
}

bool DatabaseHandler::isGameIdUsed(const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = gameColl.find_one(document {} << "game_id" << gameId << finalize);
    // check if gameId is contained in the collection
    if (maybeResult) {
        return true;
    }
    return false;
}

void DatabaseHandler::createGame(const int &gameId, const std::vector<std::string> &players, const int &nPlayers, const json &boardConfig)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];
    json playersJson;
    for (auto &player : players) {
        playersJson.push_back(player);
    }

    gameColl.insert_one(document {} << "game_id" << gameId << "players" << bsoncxx::from_json(playersJson.dump()) << "player_number" << nPlayers
                                    << "board_config" << bsoncxx::from_json(boardConfig.dump()) << finalize);
}

json DatabaseHandler::getGameBoardConfig(const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = gameColl.find_one(document {} << "game_id" << gameId << finalize);
    // check if gameId is contained in the collection
    if (maybeResult) {
        auto gameView = maybeResult->view();
        auto boardConfig = gameView["board_config"].get_document().view();
        json boardConfigJson = json::parse(bsoncxx::to_json(boardConfig));
        return boardConfigJson;
    }
    return json();
}

json DatabaseHandler::getGameConfig(const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = gameColl.find_one(document {} << "game_id" << gameId << finalize);
    // check if gameId is contained in the collection
    if (maybeResult) {
        auto gameView = maybeResult->view();
        json gameConfigJson = json::parse(bsoncxx::to_json(gameView));
        gameConfigJson.erase("_id");
        return gameConfigJson;
    }
    return json();
}

std::vector<int> DatabaseHandler::getPlayerGameIds(const std::string &username)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // check if usernames are contained in the collection
    if (maybeResult) {
        auto userView = maybeResult->view();
        auto userViewBson = bsoncxx::to_json(userView);
        json userViewJson = json::parse(userViewBson);
        json acceptedGameIdsJson = userViewJson["accepted_gameId"];
        std::vector<int> gameIds;
        for (auto &gameId : acceptedGameIdsJson) {
            gameIds.push_back(gameId);
        }
        return gameIds;
    }
    return std::vector<int>();
}

std::vector<int> DatabaseHandler::getPlayerInviteGameIds(const std::string &username)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = userColl.find_one(document {} << "username" << username << finalize);
    // check if usernames are contained in the collection
    if (maybeResult) {
        auto userView = maybeResult->view();
        auto userViewBson = bsoncxx::to_json(userView);
        json userViewJson = json::parse(userViewBson);
        json inviteGameIdsJson = userViewJson["invite_gameId"];
        std::vector<int> gameIds;
        for (auto &gameId : inviteGameIdsJson) {
            gameIds.push_back(gameId);
        }
        return gameIds;
    }
    return std::vector<int>();
}

void DatabaseHandler::deleteGame(const int &gameId)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];
    // get players_username
    bsoncxx::stdx::optional<bsoncxx::document::value> maybeResult = gameColl.find_one(document {} << "game_id" << gameId << finalize);
    // check if gameId is contained in the collection
    if (maybeResult) {
        auto gameView = maybeResult->view();
        auto gameViewBson = bsoncxx::to_json(gameView);
        json gameViewJson = json::parse(gameViewBson);
        json playersJson = gameViewJson["players"];
        for (auto &player : playersJson) {
            // delete player from user collection
            removeGameIdFromUser(player, gameId);
        }
        // delete game from game collection
        gameColl.delete_one(document {} << "game_id" << gameId << finalize);
    }
}

void DatabaseHandler::setGameBoardConfig(const int &gameId, const json &boardConfig)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection gameColl = Instance()->db[database::kGameCollectionName];
    gameColl.update_one(document {} << "game_id" << gameId << finalize,
        document {} << "$set" << open_document << "board_config" << bsoncxx::from_json(boardConfig.dump()) << close_document << finalize);
}

json DatabaseHandler::getLeaderboard(const int &nPlayers)
{
    std::lock_guard<std::mutex> guard {m_dbMutex};

    mongocxx::collection userColl = Instance()->db[database::kUserCollectionName];

    auto order = document {} << "elo" << -1 << finalize;
    auto opts = mongocxx::options::find {};
    opts.limit(nPlayers);
    opts.sort(order.view());
    auto cursor = userColl.find({}, opts);

    json leaderboard;
    for (auto doc : cursor) {
        auto usersViewBson = bsoncxx::to_json(doc);
        json usersViewJson = json::parse(usersViewBson);
        leaderboard.push_back(json {{"username", usersViewJson["username"]}, {"elo", usersViewJson["elo"]}});
    }

    return leaderboard;
}