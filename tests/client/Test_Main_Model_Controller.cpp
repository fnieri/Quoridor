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

    /* 1. Sending a friend request : Bob asks John as friend */
    /*
    json friend_request = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "Bob", "John");
    controller.processRequest(friend_request.dump());
    bool is_found = false;
    std::vector<std::string> friendsRequestSentList = *(model->getFriendRequestsSent());
    for (auto &aFriend : friendsRequestSentList) {
        if (aFriend == "Bob")
            is_found = true;
    }
    REQUIRE(is_found);
    */

    /* 2. Accept a friend request : John accepts Bob */
    /*
    json msg2 = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, "Bob", "John");
    controller.processRequest(msg2.dump());
    // How do we check from Bob's pov that he got the request

    // Checking if Bob is in John's friend list
    is_found = false;
    std::vector<std::string> friendsList = *(model->getFriendList());
    for (auto& aFriend: friendsList) { if (aFriend == "Bob") is_found=true;}
    REQUIRE(is_found);
    */

    /* 3. Remove Friend : John removes Bob of his friends */
    /*
    json msg3 = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REMOVE, "John", "Bob");
    controller.processRequest(msg3.dump());
    is_found = false;
    std::vector<std::string> friendsListUpdate = *(model->getFriendList());
    for (auto &aFriend : friendsListUpdate) {
        if (aFriend == "Bob")
            is_found = true;
    }
    REQUIRE(!is_found);
    */

    /* 4. Refuse Friend Request */
    /*
    json msg = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "John", "Laura");
    controller.processRequest(msg.dump());
    json msg2 = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REFUSE, "Laura", "John");
    controller.processRequest(msg2.dump());

    // REQUIRE()    // what is required here ? we cant get Lauras friend request list ?

    */


    /* ---------- CHAT BOX Request ---------- */

    /* 1. Sending Direct Messages */
    /*
    // Bob sends a message to John
    json request = SerializableMessageFactory::serializeFriendMessage("Bob", "John", "Hello it's Bob");
    controller.processRequest(request.dump());

    // Searching for the message sent
    bool is_found = false;
    std::vector<std::string> bobsChat = *(model->getChatWith("Bob"));
    for (auto &aMsg : bobsChat) {
        if (aMsg == "Hello it's Bob")
            is_found = true;
    }
    REQUIRE(is_found);

    // Searching for a message not sent (should be false)
    is_found = false;
    for (auto &aMsg : bobsChat) {
        if (aMsg == "Should we start a game ?")
            is_found = true;
    }
    REQUIRE(!is_found);
    */

    /* 2. Sending Group Message */
    /*
        // This has to do with the GameModel ?
    */


    /* ---------- RESOURCE_REQUEST Request ---------- */

    /* 1. Leaderboard Request */
    /*
    // We have to make the Leaderboard ? and make it a serializable data ?
    std::vector<std::pair<std::string, float>> leaderBoard{std::make_pair("John", 2.0), std::make_pair("Lucia", 29.0), std::make_pair("Bob", 0.0)};
    json request = SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD);
    // json request = SerializableMessageFactory::serializeAnswerExchange(DataType::LEADERBOARD, ???);
    controller.processRequest(request.dump());
    std::vector<std::pair<std::string, float>> leaderBoardReceived = *model->getLeaderboard();
    REQUIRE(leaderBoard == leaderBoardReceived);
    */

    /* 2. All Friends List Request */
    /*
    // Sending the request
    controller.processRequest(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "John", "Bob").dump());
    controller.processRequest(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "John", "Lucia").dump());

    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::FRIEND_REQUESTS_SENT).dump());

    std::vector<std::string> friendsRequestSentList{"Bob", "Lucia"};
    REQUIRE(friendsRequestSentList == *model->getFriendRequestsSent());
    std::vector<std::string> wrongFriendsRequestSentList{"Lucia"};
    REQUIRE(wrongFriendsRequestSentList != *model->getFriendRequestsSent());

    // Friends accept, so are supposedly in the friend's list now
    controller.processRequest(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, "Lucia", "John").dump());
    controller.processRequest(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, "Bob", "John").dump());

    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::FRIENDS_LIST).dump());

    std::vector<std::string> friendsList{"Bob", "Lucia"};
    REQUIRE(friendsList == *model->getFriendList());
    std::vector<std::string> wrongFriendsList{"Lucia"};
    REQUIRE(wrongFriendsList != *model->getFriendList());

    // Some people send invite (only checking request lists)
    controller.processRequest(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "Mustafa", "John").dump());
    controller.processRequest(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "Patrick", "John").dump());
    controller.processRequest(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "Lola", "John").dump());

    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::FRIEND_REQUESTS_RECEIVED).dump());

    std::vector<std::string> friendsRequestReceivedList{"Mustafa", "Patrick", "Lola"};
    REQUIRE(friendsRequestReceivedList == *model->getFriendRequestsReceived());
    std::vector<std::string> wrongFriendsRequestReceivedList{"Patrick"};
    REQUIRE(wrongFriendsRequestReceivedList != *model->getFriendRequestsReceived());
    */

    /* 3. Game Configuration Request */
    /*
    // is this abt GameMode or ? should i fake a game for the tests ?
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::GAME_CONFIG).dump());
    */

    /* 4. Game ID Request */
    /*
    // the game id is given by the server .. ?
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::GAME_IDS).dump());
    */

    /* 5. Chats Request */
    /*
    controller.processRequest(SerializableMessageFactory::serializeFriendMessage("Bob", "John", "Hello it's Bob").dump());
    controller.processRequest(SerializableMessageFactory::serializeFriendMessage("John", "Bob", "Hello how are you").dump());
    controller.processRequest(SerializableMessageFactory::serializeFriendMessage("Bob", "John", "Find let's play a game").dump());

    // how do we ask for the chats between Bob and John
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::CHATS).dump());

    // REQUIRE();
    */

    /* 6. ELO Request */
    /*
    float johnsELO = 12;
    model->setELO(12);
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::ELO).dump());
    // REQUIRE(12 == *model->getELO());     // also doesnt make sense
    */


    /* ---------- IN_GAME_RELATED Request ---------- */
    /*
     * Not implemented yet in Models/Controllers
     */


    /* ---------- GAME_SETUP Request ---------- */
    /*
     * Not implemented yet in Models/Controllers
     * */


    // Louis' comments
    /*
    You must test every requests that controller can process
    To test a request, you must call the processRequest(std::string request) in MainController. The request string must be a valid json converted to string
    To test if a request worked, you must call the appropriate getter in the model. For example, model->getLeaderboard() will return the leaderboard
    You may use DatabaseHandler to fetch data but that is not mandatory
    At the moment only a few tests will work (for example, the leaderboard should work)
    */
}