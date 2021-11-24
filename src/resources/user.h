#ifndef __USER_H
#define __USER_H

#include <string>
#include <memory>
#include <vector>
#include "chatbox.h"

class User {
    private:
        std::string username;
        std::vector<std::string> friendsList;
        int ELO;
        bool isLoggedIn;
    public:
        User();
        User(std::string username);
        ~User();
        std::string getUsername();
        std::vector<std::string> getFriendsList();
        int getELO();
        void setELO();
        void logIn();
        void registerAccount();
        void logOut();
        void checkLeaderboard();
        void accesSettings();
        void addFriend(std::string username);
        void removeFriend(std::string username);
        void connectToChat(ChatBox chat);
        void sendMessage(Message message);
        void play(std::string mod);
        void inviteFriendsToMatch();
        void joinFriendsMatch();
        void askToPauseMatch();
        void saveMatch();
        void loadMatch();
        void displayUser();

};

#endif