#include "UserHandler.h"

/**
 * UserHandler
 */

UserHandler::UserHandler(Socket &&socket, const std::string &username)
    : SocketUser {socket}
    , m_userHandled {std::make_shared<User>(username)}
{
    std::thread th {handleInteractions};
    th.detach();
}

void UserHandler::handleInteractions()
{
    while (true) {
        auto req {json::parse(receive())};

        // TODO handle request
    }
}

/**
 * UserHub
 */
