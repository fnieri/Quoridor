#ifndef __CHATBOX_H
#define __CHATBOX_H


#include <memory>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "user.h"

class ChatBox {
    private:
        std::vector<User> usersConnected;
        FILE messagesLog;
    public:
        void receiveMessage(Message);
};

#endif 