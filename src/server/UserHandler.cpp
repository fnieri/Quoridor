/**
 * @author Boris Petrov
 */

#include "UserHandler.h"

#include "ServerUser.h"

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

bool UserHandler::isFinished() const
{
    return m_isFinished;
}

std::string UserHandler::getUsername() const
{
    return m_userHandled->getUsername();
}

void UserHandler::relayMessage(const std::string &serMessage)
{
    // TODO: verification for user updates on certain specific messages
    send(serMessage);
}

/**
 * UserHub
 */

void UserHub::eraseFinished()
{
    m_handlers.erase(std::remove_if(m_handlers.begin(), m_handlers.end(), [](const auto &h) { return h.isFinished(); }), m_handlers.end()); // <3 c++
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

void UserHub::relayMessageTo(const std::string &username, const std::string &message)
{
    auto receiver {std::find_if(m_handlers.begin(), m_handlers.end(), [username](const auto &h) { return h.getUsername() == username; })};
    receiver->relayMessage(message);
}
