#ifndef __LOGINHANDLER_H
#define __LOGINHANDLER_H

#include <string>

class loginHandler {
    private:
        std::string username;
        std::string password;
    public:

        bool processLogin();
        /* Login process checks if:
        * Username is in database
        * Hashed password with salt key matches the one in database
        * Login process is tied to server and needs to lookup database
        *   
        *   
};

#endif