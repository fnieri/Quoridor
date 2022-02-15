/**
 * @author Boris Petrov
 */

#include "UserHandler.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * UserHandler
 */

UserHandler::UserHandler(Socket &&socket, const std::string &username)
    : RequestHandler {std::move(socket)}
    , m_userHandled {std::make_shared<User>(username)}
{
}

void UserHandler::handleRequests()
{
    while (m_connected) {
        auto req {json::parse(receive())};

        // TODO handle request
    }
}

/**
 * UserHub
 */

void UserHub::eraseDisconnected()
{
    m_connectedUsers.erase(std::remove_if(m_connectedUsers.begin(), m_connectedUsers.end(), [](auto &h) { return h.isConnected(); }), m_connectedUsers.end());
}

void UserHub::addUser(Socket &&client, const std::string &username)
{
    // Start handling
    UserHandler userHandler {std::move(client), username};
    userHandler.startHandling();

    m_connectedUsers.push_back(std::move(userHandler));
}
