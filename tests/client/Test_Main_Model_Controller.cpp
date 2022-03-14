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

    /* I dont think this is useful
    // Searching for a message not sent (should be false)
    is_found = false;
    for (auto &aMsg : bobsChat) {
        if (std::string(aMsg.sentMessage) == "Should we start a game ?")
            is_found = true;
    }
    REQUIRE(!is_found);
    */

    /* 2. Sending Group Message */
    /*
        // This has to do with the GameModel ?
    */


    /* ---------- RESOURCE_REQUEST Request ---------- */
    // these tests only set a resource then ask for it with serializeRequestExchange, and then checks the value set... but in the end were only testing the model not the controller (cout)

    /* 1. Leaderboard Request */
    std::vector<std::pair<std::string, float>> leaderBoard{std::make_pair("John", 2.0), std::make_pair("Lucia", 29.0), std::make_pair("Bob", 0.0)};
    model->setLeaderboard(leaderBoard);
    json ldb_request = SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD);
    controller.processRequest(ldb_request.dump());
    std::vector<std::pair<std::string, float>> leaderBoardReceived = *model->getLeaderboard();
    REQUIRE(leaderBoard == leaderBoardReceived);


    /* 2. All Friends List Request */
    std::vector<std::string> friendsRequestSentList{"Bob", "Lucia"};
    model->setFriendRequestsSent(friendsRequestSentList);
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::FRIEND_REQUESTS_SENT).dump());
    REQUIRE(friendsRequestSentList == *model->getFriendRequestsSent());

    // dont think this is useful either when we're checking for the wrong list
    REQUIRE(std::vector<std::string>{"Lucia"} != *model->getFriendRequestsSent());

    // Friends accept, so are supposedly in the friend's list now
    model->setFriendList(friendsRequestSentList);
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::FRIENDS_LIST).dump());

    REQUIRE(friendsRequestSentList == *model->getFriendList());
    REQUIRE(std::vector<std::string>{"Lucia"} != *model->getFriendList());

    // Some people send invite (only checking request lists)
    model->setFriendRequestsReceived(std::vector<std::string>{"Mustafa", "Patrick", "Lola"});
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::FRIEND_REQUESTS_RECEIVED).dump());

    REQUIRE(std::vector<std::string>{"Mustafa", "Patrick", "Lola"} == *model->getFriendRequestsReceived());
    REQUIRE(std::vector<std::string>{"Patrick"} != *model->getFriendRequestsReceived());


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
    model->addFriend("Sarah");
    controller.processRequest((SerializableMessageFactory::serializeFriendMessage("Sarah", "John", "Hello it's Bob")).dump());
    controller.processRequest((SerializableMessageFactory::serializeFriendMessage("Sarah", "John", "Fine let's play a game")).dump());

    controller.processRequest((SerializableMessageFactory::serializeRequestExchange(DataType::CHATS)).dump());

    std::vector<Message> chats{Message{"Sarah", "Hello it's Bob"}, Message{"Sarah", "Fine let's play a game"}};
    std::vector<Message> BJ_chats = *model->getChatWith("Sarah");
    REQUIRE(chats == BJ_chats);


    /* 6. ELO Request */

    float johnsELO = 12;
    model->setElo(12);
    controller.processRequest(SerializableMessageFactory::serializeRequestExchange(DataType::ELO).dump());
    REQUIRE(johnsELO == *model->getELO());     // also doesnt make sense



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