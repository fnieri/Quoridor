#pragma once


#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include "User.h"

// struct use for message info
struct Message {
        time_t timeSent;
        User sender;
        User receiver;
        std::string sentMessage;
};


