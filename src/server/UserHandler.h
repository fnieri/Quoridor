/**
 * @author Boris Petrov
 */

#pragma once

#include "User.h"

#include "src/common/SocketUser.h"

class UserHandler : public SocketUser
{
private:
    std::shared_ptr<User> m_userHandled;
    std::shared_ptr<GameHandler> m_game {}; // nullptr

public:
    UserHandler(Socket &&, const std::string &);

    void handleInteractions();
};

class UserHub
{
private:
    std::vector<std::shared_ptr<UserHandler>> m_connectedUsers;

public:
    UserHub();

    void addUser(Socket &&, const std::string &);
};
