//
// Created by louis on 3/10/22.
//

#include <catch2/catch.hpp>

#include "src/client/MainController.h"
#include "src/client/MainModel.h"
#include "src/common/SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <memory>
#include <vector>
#include <utility>


using json = nlohmann::json;

SCENARIO("Testing requests")
{
    MainController controller; // only call process request
    MainModel *model = controller.getMainModel();

    // All domains of requests :

    /* ---------- AUTH REQUEST ---------- */

    json auth_request = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::LOGIN, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT, "John");
    controller.processRequest(auth_request.dump());
    REQUIRE(model->isLoggedIn());
    REQUIRE(std::string(*model->getUsername()) == std::string("John"));


    /* ---------- RELATION REQUEST ---------- */

    /* 1. Sending a friend request : John asks Bob as friend */
    json friend_request = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "Bob", "John");
    controller.processRequest(friend_request.dump());
    bool is_found = false;
    std::vector<std::string> friendsRequestReceivedList = *(model->getFriendRequestsReceived());
    for (auto &aFriend : friendsRequestReceivedList) if (std::string(aFriend) == std::string("Bob")) is_found = true;
    REQUIRE(is_found);


    /* 2. Accept a friend request : John accepts Bob */
    // How do we check from Bob's pov that he got the request

    json friend_made = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, "John", "Bob");
    controller.processRequest(friend_made.dump());

    // Checking if Bob is in John's friend list
    is_found = false;
    std::vector<std::string> friendsList = *(model->getFriendList());
    for (auto& aFriend: friendsList)  if (std::string(aFriend) == std::string("Bob")) is_found = true;
    REQUIRE(is_found);


    /* 3. Remove Friend : John removes Bob of his friends */

    json friend_remove = SerializableMessageFactory::serializeFriendRemove("John", "Bob");
    controller.processRequest(friend_remove.dump());
    is_found = false;
    std::vector<std::string> friendsListUpdate = *(model->getFriendList());
    for (auto &aFriend : friendsListUpdate) if (std::string(aFriend) == std::string("Bob")) is_found = true;
    REQUIRE(!is_found);


    /* 4. Refuse Friend Request : John asks Laura but she refuses */
    json msg = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "John", "Laura");
    controller.processRequest(msg.dump());
    json msg2 = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REFUSE, "Laura", "John");
    controller.processRequest(msg2.dump());

    is_found = false;
    std::vector<std::string> friendsRequestReceivedList2 = *(model->getFriendRequestsReceived());
    for (auto &aFriend : friendsRequestReceivedList2) if (std::string(aFriend) == std::string("Laura")) is_found = true;
    REQUIRE(!is_found);



    /* ---------- CHAT BOX Request ---------- */

    /* 1. Sending Direct Messages */

    // Bob sends a message to John
    json msg_sending = SerializableMessageFactory::serializeFriendMessage("Bob", "John", "Hello it's Bob");
    controller.processRequest(msg_sending.dump());

    // Searching for the message sent
    is_found = false;
    std::vector<Message> bobsChat = *(model->getChatWith("Bob"));
    for (auto &aMsg : bobsChat) {
        if (std::string(aMsg.sentMessage) == std::string("Hello it's Bob"))
            is_found = true;
    }
    REQUIRE(is_found);


    /* 2. Sending Group Message */


    /* ---------- RESOURCE_REQUEST Request ---------- */
    /* 1. Friends List Request */
    std::vector<std::string> friendList{"anne-marie", "leo", "francesco", "nargis"};
    json jsonfriendList = json(friendList);
    auto friendListReq = SerializableMessageFactory::serializeAnswerExchange(DataType::FRIENDS_LIST, jsonfriendList);
    controller.processRequest(friendListReq.dump());
    auto friendsListModel = *model->getFriendList();
    REQUIRE(friendsListModel == friendList);

    /* 1. Leaderboard Request */
    std::vector<std::pair<std::string, float>> leaderBoard{ std::make_pair("John", 2.0), std::make_pair("Lucia", 29.0), std::make_pair("Bob", 0.0)};
    json jsonLeaderboard;
    for (auto el : leaderBoard) jsonLeaderboard.push_back(json {{"username", el.first}, {"elo", el.second}});
    json ldb_request = SerializableMessageFactory::serializeAnswerExchange(DataType::LEADERBOARD, jsonLeaderboard);
    controller.processRequest(ldb_request.dump());
    std::vector<std::pair<std::string, float>> leaderBoardReceived = *model->getLeaderboard();
    REQUIRE(leaderBoard == leaderBoardReceived);

    /* 3. Game Configuration Request */
    
    /* 4. Game ID Request */
    
    /* 5. Chats Request */
   
    /* 6. ELO Request */


    /* ---------- IN_GAME_RELATED Request ---------- */


    /* ---------- GAME_SETUP Request ---------- */
    
    
}