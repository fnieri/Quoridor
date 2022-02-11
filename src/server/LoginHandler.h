/**
 * @author Francesco Nieri
 * @author Boris Petrov
 */

#pragma once

#include "src/common/SocketUser.h"

#include <atomic>
#include <string>

/**
 * Login process checks if:
 * - Username is in database
 * - Hashed password with salt key matches the one in database
 *
 * The LoginHandler takes care of this process by receiving the
 * requests of the client (effectively ignoring everything not
 * related to log in).
 */
class LoginHandler : public SocketUser
{
private:
    std::atomic<bool> m_isLogging {true};
    bool doesUsernameExist(const std::string &);
    bool isPasswordCorrectFor(const std::string &, const std::string &);

public:
    LoginHandler(Socket &&);

    void processLogin();
    bool isLogging() const;
};

class LoginHub
{
private:
    std::vector<LoginHandler> m_handlers;
    void eraseFinishedHandlers();

public:
    LoginHub()
    {
    }

    void addClient(Socket &&);
    void clientWasLoggedInWith(Socket &&, const std::string &);
};
