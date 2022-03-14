#pragma once

#include <string>

// struct use for message info
struct Message {
    //    time_t timeSent;
    std::string sender;
    std::string sentMessage;
    bool operator==(const Message& b) const
    {
        return (this->sender == b.sender) && (this->sentMessage == b.sentMessage);
    }
};
