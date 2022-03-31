/**
 * @file AuthHandler.h
 * @author Boris Petrov
 * @brief Register and log clients in
 * @date 02/25/22
 */

#pragma once

#include <string>

class UserHub;

/**
 * Register and log clients
 *
 * @param userHub bridge between the AuthHandler and the users
 *
 * @note Since users on the server are identified by their username,
 * the AuthHandler wouldn't know where to direct its answer if
 * the target client was not yet bound to its username (which
 * happens after the login). Thus, unlike the other handlers,
 * the AuthHandler returns its answer instead of sending it directly
 * to the client through the UserHub.
 *
 * @note Strings received by the AuthHandler shall be json formatted
 * according to the standard.
 *
 * TODO: link json standard doc here
 */
class AuthHandler
{
private:
    UserHub &m_userHub;

    /**
     * Check whether the request results in a positive register
     *
     * @param serRequest json formatted requet according to the standard
     * @return requestAnswer json formatted answer according to the standard
     */
    std::string tryRegister(const std::string &);
    /**
     * Check whether the request results in a positive login
     *
     * @param serRequest json formatted requet according to the standard
     * @return requestAnswer json formatted answer according to the standard
     */
    std::string tryLogIn(const std::string &);

public:
    AuthHandler(UserHub &);

    /**
     * Analyse the request and act accordingly
     *
     * @param message message to be processed
     * @return requestAnswer json formatted response
     *
     * @note If the message is a register action, check whether the username
     * already exists and if not, record the user in the DB and send him a
     * confirmation. Otherwise, it must be a login. Check the credentials and let
     * him in if they're correct.
     */
    std::string processRequest(const std::string &);
};
