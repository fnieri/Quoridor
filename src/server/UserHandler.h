/**
 * @author Boris Petrov
 */

#pragma once

#include "RequestHandler.h"
#include "src/common/SocketUser.h"

#include <memory>

/* #include "GameHandler.h" */
/* #include "User.h" */

struct User {
    std::string username;
};

class GameHandler;

class UserHandler : public RequestHandler
{
private:
    bool m_connected {true};
    std::shared_ptr<User> m_userHandled;
    std::shared_ptr<GameHandler> m_game {}; // nullptr

    void handleRequests() override;

public:
    UserHandler(Socket &&, const std::string &);

    bool isConnected() const
    {
        return m_connected;
    }
};

// TODO: maybe make a superclass Hub ?
class UserHub
{
private:
    std::vector<std::shared_ptr<UserHandler>> m_connectedUsers;

public:
    UserHub();

    void addUser(Socket &&, const std::string &);
};
