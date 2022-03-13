#include "TerminalVue.h"
// #include "MainController.h"
// #include "src/common/SerializableMessageFactory.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
//#include "src/client/MainController.h"
//#include "src/client/MainModel.h"
#include "src/common/SerializableMessageFactory.h"

int main(int argc, char* argv[])
{
//MainModel model;
//std::vector<std::pair<std::string, float>> testLeaderBoard{};
//model.setLeaderboard(std::vector<std::string>);

//    if (argc < 2) {
//        std::cerr << "Missing arguments. Use --help for information" << std::endl;
//        return 1;
//    } else if (strcmp(argv[1], "--help") == 0) {
//        std::cout << "Usage: ./client [--help] [--server=<server_ip>]" << std::endl;
//        return 0;
//    }
//    else if (strcmp(argv[1], "--server") == 0) {
//        if (argc != 3) {
//            std::cerr << "Missing arguments. Use --help for information" << std::endl;
//            return 1;
//        }
//        setenv("SERVER_IP", argv[2], 1);
//        std::cout << "Server started" << std::endl;
//    }

    // GameController gameController {2, 0, 1};

    // gameController.logIn("testing", "testingPassword");

    // std::cout << gameController.getLeaderboard() << std::endl;
    // std::cout << gameController.getFriendList() << std::endl;

    system("clear");
    TerminalVue vue;
    std::thread t1(&TerminalVue::run, &vue);
    vue.addChatMessage("User", "Hello World !");
    t1.join();

    // sleep(15);

    return 0;
};