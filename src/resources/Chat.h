#ifndef CHAT
#define CHAT
#include <string>
#include <iostream>

// used to store messages and read messages
class Chat {
    std::string message;
public:
    Cell(/* args */);

    ~Cell();

    write(std::string message);
    read();
};


#endif  // CHAT