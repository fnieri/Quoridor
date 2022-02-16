/**
 * @author Boris Petrov
 */

#pragma once

#include <string>

class ChatBox
{
private:
    std::vector<User> usersConnected;
    FILE messagesLog;

public:
    void receiveMessage(Message);
};
