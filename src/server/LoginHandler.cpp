/**
 * @author Boris Petrov
 */

#include "LoginHandler.h"

#include <json/core.h> // TODO: maybe not the whole thing !?

#include <thread>

/**
 * LoginHandler
 */

LoginHandler::LoginHandler(Socket &&client)
    : SocketUser {client}
{
    std::thread th {processLogin};
    th.detach();
}

void LoginHandler::processLogin()
{
    bool loggedIn {false};
    std::string username {};

    // TODO finish this
    while (!loggedIn) {
        auto request {json::parse(receive())};

        if (request["Type"] == "LogIn") {
            std::cout << "Loggin in";

        } else if (request["Type"] == "Register") {
            std::cout << "Registring";
        }
    }

    m_isLogging = false;
}

/**
 * LoginHub
 */

void LoginHub::eraseFinishedHandlers()
{
    m_handlers.erase(std::remove_if(m_handlers.begin(), m_handlers.end(), [](auto h) { return h.isLogging(); }), m_handlers.end());
}

void LoginHub::addClient(Socket &&client)
{
    m_handlers.emplace_back(client);
}

void LoginHub::clientWasLoggedInWith(Socket &&client, const std::string &username)
{
    m_userHub.addUser(client, username);
    eraseFinishedHandlers();
}
