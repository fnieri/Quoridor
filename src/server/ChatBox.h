#pragma once

#include "User.h"
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

class ChatBox
{
private:
    std::vector<User> usersConnected;
    FILE messagesLog;

public:
    void receiveMessage(Message);
};
