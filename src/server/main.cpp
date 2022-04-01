/**
 * @file main.cpp
 * @author Boris Petrov
 * @brief Server's main
 * @date 02/25/22
 */

#include "Config.h"
#include "ConfigEnums.h"
#include "Database.h"
#include "LandingPool.h"
#include "ServerUser.h"
#include "UserHandler.h"

int main(int argc, char *argv[])
{
    unsigned short port = stoi(ConfigHandler::Instance()->getServerProperty(ServerProperty::PORT));
    std::cout << "Server started on port " << port << std::endl;
    UserHub userHub;
    LandingPool entryDoor {port, userHub};
    DatabaseHandler::sendFriendRequest("testing", "bar");

    return entryDoor.openToConnections();
}
