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
    auto recordMessage(const std::string &) -> void;
    /**
     * Send it to connected users
     *
     * @param request json formatted request representing a message
     */
    auto relayMessage(const std::string &) -> void;

public:
    ChatBox(UserHub &);

    /**
     * Analyse the message, record it and relay it
     *
     * @param message message to be processed
     */
    auto processRequest(const std::string &) -> void;
};
