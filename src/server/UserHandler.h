/**
 * @author Francesco Nieri
 * @author Boris Petrov
 */

#pragma once

#include "RequestHandler.h"
#include "src/common/Observer.h"

#include <atomic>
#include <string>

/**
 * Login process checks if:
 * - Username is in database
 * - Hashed password with salt key matches the one in database
 *
 * The UserHandler takes care of this process by receiving the
 * requests of the client (effectively ignoring everything not
 * related to log in).
 */
class UserHandler : public RequestHandler, public Subject
{
private:
    bool m_isFinished {true};

protected:
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
};
