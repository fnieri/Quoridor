#include "TerminalVue.h"
// #include "MainController.h"
// #include "src/common/SerializableMessageFactory.h"
#include <unistd.h>
#include <iostream>


int main()
{
    // MainController controller {"localhost", 12345};
    // controller.startHandling();
    
    // auto req {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, "foo", "1245").dump()};
    // // auto reqFriendReq {SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "foo", "bar").dump()};

    // auto ans = controller.getSyncAnswer(req);
    // std::cerr << ans << std::endl;

    // sleep(2);

    // auto reqA {SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, "foo", "12345").dump()};
    // // auto reqFriendReq {SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, "foo", "bar").dump()};

    
    // auto ansA = controller.getSyncAnswer(reqA);
    // std::cerr << ansA << std::endl;

    system("clear");
    TerminalVue vue; 
    std::thread t1(&TerminalVue::run, &vue);
    vue.addChatMessage("User", "Hello World !");
    t1.join();

    // sleep(15);

    return 0;
};