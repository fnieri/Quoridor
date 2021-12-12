#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include "user.h"

// struct use for message info
struct Message {
        time_t timeSent;
        User sender;
        User receiver;
        std::string sentMessage;
};



#endif
