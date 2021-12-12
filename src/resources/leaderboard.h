#ifndef __LEADERBOARD_H
#define __LEADERBOARD_H

#include <vector>
#include "user.h"
class Leaderboard {
    private:
        std::vector<User> listOfUsers;
    public:
        //Calls to database to get sorted users by ELO
        std::vector<User> getTopUsers();
        void sortBy();
        void filterBy();
};

#endif