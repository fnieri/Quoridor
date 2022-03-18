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
//    serverController.fetchFriendMessages("testing", "testingFriend");
//    auto model = mainController.getMainModel();
//    auto mess = model->getChatWith("testingFriend");
//    while (true) {
//        std::cout << "ahhhh" << std::endl;
//        for (const auto &m : *mess) {
//            std::cout << m.sentMessage << std::endl;
//            return 0;
//        }
//        sleep(0.1);
//    }
//    sleep(2);
    //    serverController.fetchLeaderboard();
    //    serverController.fetchFriends();
    //    serverController.fetchElo();
    //    //        auto leaderboard = ;
    //    std::cout << *(model->getELO()) << std::endl;

    system("clear");
    TerminalVue vue;
    vue.run();

    //    std::thread t1(&TerminalVue::run, &vue);
    //    t1.join();

    return 0;
};