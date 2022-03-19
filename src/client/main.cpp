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
    //    //    serverController.login("testing", "testingPassword");
    //    serverController.login("ok", "k");
    //    auto model = mainController.getMainModel();
    //
    //    serverController.fetchData();
    //    model->getUsername();
    //    model->getFriendList();
    //    if (model->getFriendRequestsReceived()->empty()) std::cout << "No friend requests received" << std::endl;
    //    else std::cout << "Friend requests received: " << std::endl;
    //    sleep(2);
    //
    //    model->getUsername();
    //    auto friendList = model->getFriendList();
    //    for (const auto& f : *friendRequestsReceived) {
    //        std::cout << f << std::endl;
    //    }

    system("clear");
    TerminalVue vue;
    vue.run();
    //
    //        std::thread t1(&TerminalVue::run, &vue);
    //        t1.join();

    return 0;
};