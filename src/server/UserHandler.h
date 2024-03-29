/**
 * @file UserHandler.cpp
 * @author Francesco Nieri
 * @author Boris Petrov
 * @brief Handle requests from client and relay them to appropriate handler
 * @date 02/25/22
 */

#pragma once

#include "AuthHandler.h"
#include "GameHandler.h"
#include "RelationsHandler.h"
#include "src/common/Observer.h"
#include "src/common/RequestHandler.h"

#include <atomic>
#include <memory>
#include <mutex>
#include <string>

class ServerUser;
class UserHub;
class ChatBox;
class GameHub;
class GameHandler;

/**
 * Take care of exchanges with a client
 *
 * The UserHandler receives messages, interprets messages
 * and sends messages. The sendings may be direct
 * consequences of received messages or not. See notes.
 *
 * @param socket from where information will come and to where it will go
 *
 * @note A direct consequence may be when asked for a specific
 * component like the list of friends. An indirect one will
 * be when the user receives a chatbox message.
 *
 * @note Usually, the messages sent and received are json formatted
 * strings.
 *
 * @note The observer pattern is used to inform who's watching
 * that the connection with the socket (that is the client) was
 * lost. This can be used to delete the UserHandler for example.
 *
 * @see UserHandler
 */
class UserHandler : public RequestHandler
{
protected:
    // A pointer is used to allow the moving of UserHandlers
    UserHub *m_userHub;
    std::shared_ptr<AuthHandler> m_authHandler;
    std::shared_ptr<RelationsHandler> m_relationsHandler;
    std::shared_ptr<ChatBox> m_chatboxHandler;
    std::shared_ptr<GameHub> m_gameHub;

    bool m_isFinished {false};
    bool m_wasTerminated {false};
    std::weak_ptr<GameHandler> m_activeGame;

    std::shared_ptr<ServerUser> m_userHandled;

    std::mutex m_syncRequest;

    /**
     * Receive messages from one user
     *
     * The message received by the handler is analyzed and
     * transferred to the appropriate specific component (e.g
     * LoginHandler, GameHandler, etc).
     *
     *                       ChatBox
     *                     /
     * User -- UserHandler
     *                     \ GameHandler
     */
    void handleRequests() override;
    void processRequest(const std::string &);

    void processAuth(const std::string &);
    void processRelations(const std::string &);
    void processChatbox(const std::string &);
    void processResourceRequest(const std::string &);
    void processGameSetup(const std::string &);
    void processGameAction(const std::string &);

public:
    UserHandler(Socket &&, UserHub *, std::shared_ptr<AuthHandler>, std::shared_ptr<RelationsHandler>, std::shared_ptr<ChatBox>, std::shared_ptr<GameHub>);

    UserHandler(const UserHandler &) = delete;
    UserHandler(UserHandler &&) = default;

    UserHandler &operator=(const UserHandler &) = delete;
    UserHandler &operator=(UserHandler &&) = default;

    bool isLoggedIn() const noexcept;
    bool isInGame() const noexcept;
    bool isFinished() const noexcept;

    std::string getUsername() const noexcept;

    void terminate();

    /**
     * Send message passing first by the handler
     *
     * This can be for instance useful for friend requests where
     * the message should both update the server and send the
     * message to the client.
     */
    void relayMessage(const std::string &);
};

/**
 * Aggregate of UserHandlers and bridge between them
 *
 * @note To the server, each client is identified by its socket
 * but between clients, they identify themselves by username.
 */
class UserHub
{
private:
    std::vector<std::shared_ptr<UserHandler>> m_handlers;
    mutable std::mutex m_handlersMutex;

    std::shared_ptr<AuthHandler> m_authHandler;
    std::shared_ptr<RelationsHandler> m_relationsHandler;
    std::shared_ptr<ChatBox> m_chatboxHandler;
    std::shared_ptr<GameHub> m_gameHub;

    /**
     * Get pointer to UserHandler of giver username
     *
     * @param username username to search for
     *
     * @returns The smart ptr to the user if he
     * is connected, otherwise a nullptr.
     */
    auto getUser(const std::string &) const;

public:
    UserHub();
    ~UserHub();

    /**
     * Add client (identified by its socket)
     *
     * @param socket socket of the new client
     *
     * @note This assigns a socket to its Handler
     * and starts the communication with it.
     *
     * @see UserHandler
     */
    void add(Socket &&);
    /**
     * Erase handlers whose connection with the client was lost
     */
    void eraseFinished();

    /**
     * Send message to someone, passing first by the handler
     *
     * @param username destinary of the message
     * @param message ditto (serialized in json)
     *
     * @warning If the targeted user in not connected,
     * the message will simply be ignored
     */
    void relayMessageTo(const std::string &, const std::string &);

    bool isInGame(const std::string &) const noexcept;
    bool isConnected(const std::string &) const noexcept;

    int connectedUsers() const noexcept;
    std::vector<std::string> namesOfConnectedUsers();
};
