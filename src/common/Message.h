#pragma once

#include "User.h"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

// struct use for message info
struct Message {
    time_t timeSent;
    User sender;
    User receiver;
    std::string sentMessage;
};
