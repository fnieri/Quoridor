/**
 * @author Boris Petrov
 */

#pragma once

#include <string>

class UserHub;

/**
 * Receive, record and relay chatbox messages
 *
 * @param userHub bridge between ChatBox and the connected users
 *
 * @note Strings received by the ChatBox shall be json formatted
 * according to the standard.
 *
 * TODO: link json standard doc here
 */
class ChatBox
{
private:
    UserHub &m_userHub;

    /**
     * Save it in the db for future usage
     */
    void recordMessage(const std::string &);
    /**
     * Send it to connected users
     */
    void relayMessage(const std::string &);

public:
    ChatBox(UserHub &);

    /**
     * Analyse the message, record it and relay it
     *
     * @param message message to be processed
     */
    void processMessage(const std::string &);
};
