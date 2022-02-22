/**
 * @author Francesco Nieri
 * @author Boris Petrov
 */

#pragma once

#include "src/common/Observer.h"
#include "src/common/RequestHandler.h"

#include <atomic>
#include <memory>
#include <string>

// TODO: replace observer with a reference

class ServerUser;
class UserHub;

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
    UserHub *m_userHub;
    std::shared_ptr<ServerUser> m_userHandled;
    bool m_isFinished {true};
    /**
     * Receive messages from one user
     *
     * The message received by the handler is analyzed and
     * transferred to the appropriate specific component (e.g
     * LoginHangler, GameHandler, etc).
     *
     *                       ChatBox
     *                     /
     * User -- UserHandler
     *                     \ GameHandler
     */
    void handleRequests() override;

public:
    explicit UserHandler(UserHub *, Socket &&);

    UserHandler(const UserHandler &) = delete;
    UserHandler(UserHandler &&) = default;

    UserHandler &operator=(const UserHandler &) = delete;
    UserHandler &operator=(UserHandler &&) = default;

    bool isFinished() const;
    std::string getUsername() const;

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
    /**
     * Erase handlers whose connection with the client was lost
     */

public:
    UserHub()
    {
    }

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

    int connectedUsers() const noexcept;
};
