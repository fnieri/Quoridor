/**
 * @file RelationsHandler.h
 * @author Boris Petrov
 * @brief Everything to do with friends
 * @date 02/25/22
 */

#pragma once

#include <string>

class UserHub;

/**
 * Record chat messages and relay them
 *
 * The messages will be recorded in the DataBase before
 * being relayed to the targets.
 *
 * @note The relay is done here, so the processRequest method
 * is best called in a thread so as to not slow the rest of the program.
 *
 * @note Strings received by the AuthHandler shall be json formatted
 * according to the standard.
 *
 * TODO: link json standard doc here
 */
class RelationsHandler
{
private:
    UserHub &m_userHub;

    /**
     * Record the friend action in the DataBase
     *
     * @param serRequest json formatted requet according to the standard
     */
    void recordFriendAction(const std::string &);
    /**
     * Send the friend action to the other participant
     *
     * @param serRequest json formatted requet according to the standard
     *
     * @note It will try to send it. If the user receiving it is online,
     * he will receive it. Otherwise, he will see the result next he
     * connects to the server.
     */
    void relayFriendAction(const std::string &);

public:
    RelationsHandler(UserHub &);

    /**
     * Analyse the request and act accordingly
     *
     * @param message message to be processed
     * @return requestAnswer json formatted response
     */
    void processRequest(const std::string &);
};
