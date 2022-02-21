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

class ServerUser;

/**
 * The UserHandler takes care of every request coming
 * from a client.
 */
class UserHandler : public RequestHandler, public Subject
{
protected:
    std::shared_ptr<ServerUser> m_userHandled;
    bool m_isFinished {true};
    void handleRequests() override;

public:
    explicit UserHandler(Socket &&);

    UserHandler(const UserHandler &) = delete;
    UserHandler(UserHandler &&) = default;

    UserHandler &operator=(const UserHandler &) = delete;
    UserHandler &operator=(UserHandler &&) = default;

    bool isFinished() const
    {
        return m_isFinished;
    }

    std::string getUsername() const;

    /**
     * Meant to send messages passing first by the UserHandler
     * and not directly sending a string.
     *
     * This can be for instance useful for friend requests where
     * the message should both update the server and send the
     * message to the client.
     */
    void relayMessage(const std::string &);
};

class UserHub : public Observer
{
private:
    std::vector<UserHandler> m_handlers;
    void eraseFinished();

public:
    UserHub()
    {
    }

    void add(Socket &&);
    void update(Event) override;

    /**
     * @param username destinary of the message
     * @param message ditto (serialized in json)
     */
    void relayMessageTo(const std::string &, const std::string &);
};
