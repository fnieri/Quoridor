/**
 * @author Boris Petrov
 */

#include "LoginHandler.h"

#include <nlohmann/json.hpp> // TODO: maybe not the whole thing !?

#include <thread>

using json = nlohmann::json;

/**
 * LoginHandler
 */

LoginHandler::LoginHandler(Socket &&client)
    : RequestHandler {std::move(client)}
{
}

void LoginHandler::handleRequests()
{
    std::string username {};

    // TODO finish this
    while (m_isLogging) {
        auto request {json::parse(receive())};

        if (request["Type"] == "LogIn") {
            std::cout << "Loggin in";

        } else if (request["Type"] == "Register") {
            std::cout << "Registring";
        }
    }

    m_isLogging = false;
    notifyObservers();
}

/**
 * LoginHub
 */

void LoginHub::eraseFinishedHandlers()
{
    m_handlers.erase(std::remove_if(m_handlers.begin(), m_handlers.end(), [](auto &h) { return h.isLogging(); }), m_handlers.end());
}

void LoginHub::addClient(Socket &&client)
{
    // Start handling
    LoginHandler clientHandler {std::move(client)};
    clientHandler.registerObserver(this);
    clientHandler.startHandling();

    m_handlers.push_back(std::move(clientHandler));
}

void LoginHub::clientWasLoggedInWith(Socket &&client, const std::string &username)
{
    m_userHub.addUser(std::move(client), username);
    eraseFinishedHandlers();
}

void LoginHub::update(Event e)
{
    switch (e) {
        break;
    case Event::Modified:
        eraseFinishedHandlers();
    }
}
