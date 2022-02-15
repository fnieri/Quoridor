#include "TerminalVue.h"

int main()
{
    system("clear");
    TerminalVue vue;
    std::thread t1(&TerminalVue::run, &vue);
    //  sleep(3);
//    vue.run();
    for (int i = 0; i < 10; i++) {
        vue.addChatMessage("User", "test");
    };
    vue.addChatMessage("User", "Hello World !");
    t1.join();
    return 0;
};