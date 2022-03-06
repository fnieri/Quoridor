/**
 * @file ChatBox.h
 * @author Boris Petrov
 * @brief Handler of chat requests
 * @date 02/25/22
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
     *
     * @param request json formatted request representing a message
     */
    void recordMessage(const std::string &);
    /**
     * Send it to connected users
     *
     * @param request json formatted request representing a message
     */
    void relayMessage(const std::string &);

public:
    ChatBox(UserHub &);

    /**
     * Analyse the message, record it and relay it
     *
     * @param message message to be processed
     */
    void processRequest(const std::string &);
};
