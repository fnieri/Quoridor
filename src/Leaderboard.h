#pragma once


#include <vector>
#include "User.h"

class Leaderboard {
    private:
        std::vector<User> listOfUsers;
    public:
        //Calls to database to get sorted users by ELO
        std::vector<User> getTopUsers();
        void sortBy();
        void filterBy();
};
