#pragma once

#include "ChatBox.h"
#include <memory>
#include <string>
#include <vector>

class User
{
private:
    std::string username;
    std::vector<std::string> friendsList;
    int ELO;
    bool isLoggedIn;

public:
    // Default constructor is used for guest connection, user is prompted to login upon entrance of program.
    User();

    // friendsList and ELO are taken from database, database lookup is done by username
    User(std::string username);
    ~User();

    // Getters
    std::string getUsername();
    std::vector<std::string> getFriendsList();
    int getELO();

    // These function are all connected to the interface, clicking or selecting options should run these methods
    // These three functions are handled by server,
    void logIn();
    void registerAccount();
    void logOut();

    // Also connected to interface
    void checkLeaderboard();
    void accesSettings();

    // Call to database to handle requests
    void addFriend(std::string username);
    void removeFriend(std::string username);

    // These functions are connected to chat, user can connect to a chat and send a message, server handles requests
    void connectToChat(ChatBox chat);
    void sendMessage(Message message);

    // Game related functions
    void play(std::string mod);
    void inviteFriendsToMatch();
    void joinFriendsMatch();
    void askToPauseMatch();

    // Game related functions tied to database, these functions call database to either save or load a match
    void saveMatch();
    void loadMatch();

    // Call to database to show user profile attributes (username, ELO, friends....)
    void displayUser();
};
