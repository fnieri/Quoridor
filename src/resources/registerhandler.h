#ifndef __REGISTERHANDLER_H
#define __REGISTERHANDLER_H

#include <string>

class registerHandler {
    private:
        std::string email;
        std::string username;
        std::string password;
    public:
        bool processRegister();
};

#endif