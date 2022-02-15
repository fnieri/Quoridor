/**
 * @author Francesco Nieri
 * @author Boris Petrov
 */

#pragma once

#include "RequestHandler.h"
#include "UserHandler.h"
#include "src/common/Observer.h"

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
class LoginHandler : public RequestHandler, public Subject
{
private:
    bool m_isLogging {true};

    bool doesUsernameExist(const std::string &);
    bool isPasswordCorrectFor(const std::string &, const std::string &);
    void processLogin();

protected:
    void handleRequests() override;

public:
    explicit LoginHandler(Socket &&);

    LoginHandler(const LoginHandler &) = delete;
    LoginHandler(LoginHandler &&) = default;

    LoginHandler &operator=(const LoginHandler &) = delete;
    LoginHandler &operator=(LoginHandler &&) = default;

    bool isLogging() const;
};

class LoginHub : public Observer
{
private:
    UserHub &m_userHub;

    std::vector<LoginHandler> m_handlers;
    void eraseFinishedHandlers();

public:
    LoginHub(UserHub &userHub)
        : m_userHub {userHub}
    {
    }

    void addClient(Socket &&);
    void clientWasLoggedInWith(Socket &&, const std::string &);

    void update(Event) override;
};
