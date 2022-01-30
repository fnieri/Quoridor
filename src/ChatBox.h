#pragma once



#include <memory>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "User.h"

class ChatBox {
    private:
        std::vector<User> usersConnected;
        FILE messagesLog;
    public:
        void receiveMessage(Message);
};
