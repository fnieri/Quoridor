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

UserHandler::UserHandler(UserHub *userHub, Socket &&user)
    : RequestHandler {std::move(user)}
    , m_userHub {userHub}
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

    m_userHub->eraseFinished();
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
    UserHandler userHandler {this, std::move(user)};
    userHandler.startHandling();

    m_handlers.push_back(std::move(userHandler));
}

void UserHub::relayMessageTo(const std::string &username, const std::string &message)
{
    auto receiver {std::find_if(m_handlers.begin(), m_handlers.end(), [username](const auto &h) { return h.getUsername() == username; })};
    receiver->relayMessage(message);
}
