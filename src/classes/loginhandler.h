#ifndef __LOGINHANDLER_H
#define __LOGINHANDLER_H

#include <string>

class loginHandler {
    private:
        std::string username;
        std::string password;
    public:
        bool processLogin();
};

#endif