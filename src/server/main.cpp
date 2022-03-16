/**
 * @file main.cpp
 * @author Boris Petrov
 * @brief Server's main
 * @date 02/25/22
 */

#include "LandingPool.h"
#include "ServerUser.h"
#include "UserHandler.h"
#include "Database.h"

int main(int argc, char *argv[])
{
//    DatabaseHandler::sendFriendRequest("testing", "bar");
    std::cout << "Server started" << std::endl;
    UserHub userHub;
    LandingPool entryDoor {12346, userHub};
    return entryDoor.openToConnections();
}
