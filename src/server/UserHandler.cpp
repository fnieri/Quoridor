/**
 * @file UserHandler.cpp
 * @author Boris Petrov
 * @brief Handle requests from client and relay them to appropriate handler
 * @date 02/25/22
 */

#include "UserHandler.h"

#include "AuthHandler.h"
#include "ServerUser.h"
#include "src/common/Exceptions.h"

#include <nlohmann/json.hpp> // TODO: maybe not the whole thing !?

#include <thread>

using json = nlohmann::json;

/**
 * UserHandler
 */

UserHandler::UserHandler(
    Socket &&user, UserHub *userHub, std::shared_ptr<AuthHandler> authHandler, std::shared_ptr<RelationsHandler> relationsHandler, std::shared<GameHub> gameHub)
    : RequestHandler {std::move(user)}
    , m_userHub {userHub}
    , m_authHandler {authHandler}
    , m_relationsHandler {relationsHandler}
    , m_gameHub {gameHub}
{
}

void UserHandler::handleRequests()
{
    while (!m_isFinished) {
        try {
            if (hasReadActivity(1)) {
                auto serRequest {receive()};

                // Do not continue if the thread was terminated during or after the receive
                if (m_isFinished)
                    break;

                processRequest(serRequest);

            }
            // Client was disconnected
            catch (UnableToRead &)
            {
                m_isFinished = true;
            }
            catch (UnableToSend &)
            {
                m_isFinished = true;
            }
        }

        // This may crash the server if the destructor
        // of the UserHub finishes before the current thread.
        // FIXME
        m_userHub->eraseFinished();
    }
}

void UserHandler::processRequest(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    if (request["domain"] == toJsonString(Domain::AUTH)) {
        processAuth(serRequest);

    } else if (request["domain"] == toJsonString(Domain::RELATIONS)) {
        processRelations(serRequest);

    } else if (request["domain"] == toJsonString(Domain::CHAT)) {
        processChatbox(serRequest);

    } else if (request["domain"] == toJsonString(Domain::RESOURCE_REQUEST)) {
        processResourceRequest(serRequest);

    } else if (request["domain"] == toJsonString(Domain::IN_GAME_RELATED)) {
        processGameAction(serRequest);

    } else if (request["domain"] == toJsonString(Domain::GAME_SETUP)) {
        processGameSetup(serRequest);
    }
}

void UserHandler::processAuth(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    auto serAnswer {m_authHandler->processRequest(serRequest)};
    auto answer {json::parse(serAnswer)};

    if (answer["status"] == toJsonString(ServerAuthReturn::CORRECT)) {
        m_userHandled->bindTo(request["username"]);
        m_userHandled->syncWithDB();
        send(serAnswer);
    }
}

void UserHandler::processRelations(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    m_relationsHandler->processRequest(serRequest);
    m_userHandled->syncWithDB();
}

void UserHandler::processChatbox(const std::string &serRequest)
{
    auto request {json::parse(serRequest)};

    m_chatboxHandler->processRequest(serRequest);
}

void UserHandler::processResourceRequest(const std::string &serRequest)
{
    std::string requestedResource;
    // TODO
}

void UserHandler::processGameSetup(const std::string &serRequest)
{
    m_userHub->processRequest(serRequest);
}

void UserHandler::processGameAction(const std::string &serRequest)
{
    m_activeGame->processRequest(serRequest);
}

bool UserHandler::isFinished() const
{
    return m_isFinished;
}

std::string UserHandler::getUsername() const
{
    return m_userHandled->getUsername();
}

bool UserHandler::isInGame() const noexcept
{
    return static_cast<bool>(m_activeGame);
}

void UserHandler::terminate()
{
    m_isFinished = true; // TODO: use another variable, to be able to send message to client about the termination
}

void UserHandler::relayMessage(const std::string &serMessage)
{
    // TODO: verification for user updates on certain specific messages
    auto message {json::parse(serMessage)};

    if (message["domain"] == toJsonString(Domain::RELATIONS)) {
        // Sync friend lists
        m_userHandled->syncWithDB();
    }

    send(serMessage);
}

/**
 * UserHub
 */

UserHub::UserHub()
    : m_authHandler {std::make_shared<AuthHandler>(*this)}
    , m_relationsHandler {std::make_shared<RelationsHandler>(*this)}
{
}

UserHub::~UserHub()
{
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    for (auto &h : m_handlers)
        h->terminate();
}

auto UserHub::getUser(const std::string &username) const
{
    std::shared_ptr<UserHandler> userHandle;

    auto userHandleIt {std::find_if(m_handlers.begin(), m_handlers.end(), [username](const auto &h) { return h->getUsername() == username; })};

    if (userHandleIt != m_handlers.end())
        userHandler = *userHandleIt;

    return userHandle;
}

void UserHub::eraseFinished()
{
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    m_handlers.erase(std::remove_if(m_handlers.begin(), m_handlers.end(), [](const auto &h) { return h->isFinished(); }), m_handlers.end()); // <3 c++
}

void UserHub::add(Socket &&user)
{
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    // Start handling
    std::shared_ptr<UserHandler> userHandler {std::make_shared<UserHandler>(std::move(user), this, m_authHandler, m_relationsHandler, m_gameHub)};
    userHandler->startHandling();

    m_handlers.push_back(std::move(userHandler));
}

void UserHub::relayMessageTo(const std::string &username, const std::string &message)
{
    auto receiver {getUser(username)};

    if (receiver)
        receiver->relayMessage(message);
}

bool UserHub::isInGame(const std::string &username) const noexcept
{
    auto userHandle {getUser(username)};

    return userHandle->isInGame();
}

bool UserHub::isConnected(const std::string &username)
{
    auto userHandle {getUser(username)};

    return static_cast<bool>(userHandle);
}

int UserHub::connectedUsers() const noexcept
{
    // Do not give size if the size is in the process of changing (add for example)
    std::lock_guard<std::mutex> guard {m_handlersMutex};

    return m_handlers.size();
}
