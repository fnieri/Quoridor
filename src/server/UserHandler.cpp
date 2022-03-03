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
#include "src/common/SerializableMessageFactory.h"
#include "src/server/ChatBox.h"

#include <nlohmann/json.hpp> // TODO: maybe not the whole thing !?

#include <iostream>
#include <thread>

using json = nlohmann::json;

// TODO QOL, make handlers singletons

/**
 * UserHandler
 */

UserHandler::UserHandler(Socket &&user, UserHub *userHub, std::shared_ptr<AuthHandler> authHandler, std::shared_ptr<RelationsHandler> relationsHandler,
    std::shared_ptr<ChatBox> chatboxHandler, std::shared_ptr<GameHub> gameHub)
    : RequestHandler {std::move(user)}
    , m_userHub {userHub}
    , m_authHandler {authHandler}
    , m_relationsHandler {relationsHandler}
    , m_chatboxHandler {chatboxHandler}
    , m_gameHub {gameHub}
    , m_userHandled {std::make_shared<ServerUser>()}
{
}

// TODO: Replace m_isFinished with UserSocket impl
// TODO: add function to run when client is disconnected
void UserHandler::handleRequests()
{
    while (!m_isFinished && !m_wasTerminated) {
        try {
            if (hasReadActivity(1)) {
                auto serRequest {receive()};

                // Do not continue if the thread was terminated during or after the receive
                if (m_isFinished || m_wasTerminated)
                    break;

                processRequest(serRequest);

            }
        }
        // Client was disconnected
        // FIXME: unable to send may be thrown by another user
        catch (UnableToRead &) {
            m_isFinished = true;
        } catch (UnableToSend &) {
            m_isFinished = true;
        }
    }

    // Only run this if the connection was lost,
    // not if the server is shuting itself down.
    if (!m_wasTerminated && isInGame()) {
        // TODO: wait for serialize
        /* auto req {SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::SURRENDER, m_userHandled->getUsername())}; */
        /* processRequest(req.dump()); */
    }

    m_userHub->eraseFinished();
}

void UserHandler::processRequest(const std::string &serRequest)
{
    auto request(json::parse(serRequest));

    std::cerr << request << std::endl << toJsonString(Domain::RELATIONS);
    /* sleep(2); */

    if (request["domain"] == toJsonString(Domain::AUTH)) {
        processAuth(serRequest);

    } else if (isLoggedIn() && request["domain"] == toJsonString(Domain::RELATIONS)) {
        std::cerr << "in relations";
        processRelations(serRequest);

    } else if (isLoggedIn() && request["domain"] == toJsonString(Domain::CHAT)) {
        processChatbox(serRequest);

    } else if (isLoggedIn() && request["domain"] == toJsonString(Domain::RESOURCE_REQUEST)) {
        processResourceRequest(serRequest);

    } else if (isLoggedIn() && request["domain"] == toJsonString(Domain::IN_GAME_RELATED)) {
        processGameAction(serRequest);

    } else if (isLoggedIn() && request["domain"] == toJsonString(Domain::GAME_SETUP)) {
        processGameSetup(serRequest);
    }
}

void UserHandler::processAuth(const std::string &serRequest)
{
    // The auth handler is the only one returning
    // a request instead of sending it.
    auto serAnswer {m_authHandler->processRequest(serRequest)};
    auto answer(json::parse(serAnswer));

    auto request(json::parse(serRequest));

    // Login was successful, bind the connection to its username
    if (answer["action"] == toJsonString(ClientAuthAction::LOGIN) && answer["status"] == toJsonString(RequestStatus::SUCCESS)) {
        m_userHandled->bindToUsername(request["username"]);
        std::cerr << "in success" << isLoggedIn();
        m_userHandled->syncWithDB();
    }

    relayMessage(serAnswer);
}

void UserHandler::processRelations(const std::string &serRequest)
{
    m_relationsHandler->processRequest(serRequest);
    m_userHandled->syncWithDB();
}

void UserHandler::processChatbox(const std::string &serRequest)
{
    m_chatboxHandler->processRequest(serRequest);
}

void UserHandler::processResourceRequest(const std::string &serRequest)
{
    auto request(json::parse(serRequest));

    // FIXME no default value :/
    auto dataType = DataType::FRIENDS_LIST;
    json data;

    if (request["data_type"] == toJsonString(DataType::FRIENDS_LIST)) {
        data = json {m_userHandled->getFriendList()};
        dataType = DataType::FRIENDS_LIST;

    } else if (request["data_type"] == toJsonString(DataType::FRIEND_REQUESTS_SENT)) {
        data = json {m_userHandled->getFriendRequestsSent()};
        dataType = DataType::FRIEND_REQUESTS_SENT;

    } else if (request["data_type"] == toJsonString(DataType::FRIEND_REQUESTS_RECEIVED)) {
        data = json {m_userHandled->getFriendRequestsReceived()};
        dataType = DataType::FRIEND_REQUESTS_RECEIVED;
    }

    // TODO: waiting serialize
    /* } else if (request["data_type"] == toJsonString(DataType::CHATS)) { */
    /*     data = json{DatabaseHandler::getChats(m_userHandled->getUsername())}; */
    /*     dataType = DataType::CHATS; */

    /* } else if (request["data_type"] == toJsonString(DataType::LEADERBOARD)) { */
    /*     data = json{DatabaseHandler::getLeaderboard()}; */
    /*     dataType = DataType::LEADERBOARD; */
    /* else if (request["data_type"] == toJsonString(DataType::GAME_IDS)) { */
    /*     data = json{m_userHandled->getGameIDs()}; */
    /* } */

    // TODO: waiting serialize
    /* auto answer {SerializableMessageFactory::serializeAnswerExchange(dataType, data)}; */
    /* send(answer); */
}

void UserHandler::processGameSetup(const std::string &serRequest)
{
    m_gameHub->processRequest(serRequest);
}

void UserHandler::processGameAction(const std::string &serRequest)
{
    if (isInGame()) {
        auto request(json::parse(serRequest));

        // Add username to the request
        request["sender"] = m_userHandled->getUsername();

        m_activeGame.lock()->processRequest(request.dump());
    }
}

bool UserHandler::isLoggedIn() const noexcept
{
    return m_userHandled->isLoggedIn();
}

bool UserHandler::isFinished() const noexcept
{
    return m_isFinished;
}

std::string UserHandler::getUsername() const noexcept
{
    return m_userHandled->getUsername();
}

bool UserHandler::isInGame() const noexcept
{
    /* return static_cast<bool>(m_activeGame); */
    return !m_activeGame.expired();
}

void UserHandler::terminate()
{
    m_wasTerminated = true;
    m_isFinished = true;
}

void UserHandler::relayMessage(const std::string &serRequest)
{
    // TODO: verification for user updates on certain specific messages
    auto request(json::parse(serRequest));

    if (request["domain"] == toJsonString(Domain::RELATIONS)) {
        // Sync friend lists
        m_userHandled->syncWithDB();
    }

    // TODO wait serialize
    /* } else if (request["domain"] == Domain::GAME_ACTION */
    /*         && request["action"] == GameSetup::GAME_STARTED) { */
    /*     m_activeGame = m_gameHub->getGame(request["game_id"]); */

    /* } else if (request["domain"] == Domain::GAME_ACTION */
    /*         && request["action"] == GameSetup::GAME_ENDED) { */
    /*     m_activeGame.reset();

    /* } */

    send(serRequest);
}

/**
 * UserHub
 */

UserHub::UserHub()
    : m_authHandler {std::make_shared<AuthHandler>(*this)}
    , m_relationsHandler {std::make_shared<RelationsHandler>(*this)}
    , m_chatboxHandler {std::make_shared<ChatBox>(*this)}
{
}

UserHub::~UserHub()
{
    m_handlersMutex.lock();
    for (auto &h : m_handlers)
        h->terminate();
    m_handlersMutex.unlock();

    while (connectedUsers() != 0)
        sleep(1);
}

auto UserHub::getUser(const std::string &username) const
{
    std::shared_ptr<UserHandler> userHandle;

    auto userHandleIt {std::find_if(m_handlers.begin(), m_handlers.end(), [username](const auto &h) { return h->getUsername() == username; })};

    if (userHandleIt != m_handlers.end())
        userHandle = *userHandleIt;

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
    std::shared_ptr<UserHandler> userHandler {
        std::make_shared<UserHandler>(std::move(user), this, m_authHandler, m_relationsHandler, m_chatboxHandler, m_gameHub)};
    userHandler->startHandling();

    m_handlers.push_back(std::move(userHandler));
}

void UserHub::relayMessageTo(const std::string &username, const std::string &message)
{
    auto receiver {getUser(username)};

    try {
        if (receiver)
            receiver->relayMessage(message);
    }
    // In case the target disconnects during the writing
    catch (UnableToRead &) {
        // Should always be valid but who knows, better avoid them segfaults !
        if (receiver) {
            receiver->terminate();
            eraseFinished();
        }
    }
}

bool UserHub::isInGame(const std::string &username) const noexcept
{
    auto userHandle {getUser(username)};

    return userHandle->isInGame();
}

bool UserHub::isConnected(const std::string &username) const noexcept
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
