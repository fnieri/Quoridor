#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include "date.h"
#include "user.h"

struct Message {
        Date timeSent;
        User sender;
        User receiver;
        std::string sentMessage;
};



#endif
