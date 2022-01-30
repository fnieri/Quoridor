#pragma once


#include <string>

class registerHandler {
    private:
        std::string username;
        std::string password;
    public:
        bool processRegister();
        /* Process register handles register requests and process and stores data in database
        * Users are stored as such in database:
        * salt              username                hashed password
        *  2                 fnieri                  K4rm!n€505s1ø
        */
};

