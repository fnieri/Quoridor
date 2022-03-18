#include "TerminalVue.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <unistd.h>
#include <vector>

#include "MainController.h"
#include "MainModel.h"
#include "ServerController.h"

int main(int argc, char *argv[])
{
//    MainController mainController;
//    ServerController serverController {&mainController};
//    serverController.login("testing", "testingPassword");
//    auto model = mainController.getMainModel();
//
////    serverController.sendFriendRequest("test", "testing");
////    serverController.sendFriendRequest("hi", "testing");
////    serverController.sendFriendRequest("fooo", "testing");
//    serverController.fetchFriendRequestsReceived();
////
//    sleep(10);
//




    system("clear");
    TerminalVue vue;
    vue.run();

    //    std::thread t1(&TerminalVue::run, &vue);
    //    t1.join();

    return 0;
};