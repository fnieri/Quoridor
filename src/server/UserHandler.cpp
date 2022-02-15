/**
 * @author Boris Petrov
 */

#include "UserHandler.h"

#include <nlohmann/json.hpp> // TODO: maybe not the whole thing !?

#include <thread>

using json = nlohmann::json;

/**
 * UserHandler
 */

UserHandler::UserHandler(Socket &&user)
    : RequestHandler {std::move(user)}
{
}

void UserHandler::handleRequests()
{
    // TODO finish this
    while (!m_isFinished) {
        auto request {json::parse(receive())};

        if (request["Type"] == "LogIn") {
            std::cout << "Loggin in";

        } else if (request["Type"] == "Register") {
            std::cout << "Registring";
        }
    }

    notifyObservers();
}

/**
 * UserHub
 */

void UserHub::eraseFinished()
{
    m_handlers.erase(std::remove_if(m_handlers.begin(), m_handlers.end(), [](auto &h) { return h.isFinished(); }), m_handlers.end());
}

void UserHub::add(Socket &&user)
{
    // Start handling
    UserHandler userHandler {std::move(user)};
    userHandler.registerObserver(this);
    userHandler.startHandling();

    m_handlers.push_back(std::move(userHandler));
}

void UserHub::update(Event e)
{
    switch (e) {
    case Event::Modified:
        eraseFinished();
        break;
    default:
        break;
    }
}
