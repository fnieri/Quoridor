/**
 * @author Boris Petrov
 */

#include "LandingPool.h"
#include "ServerUser.h"
#include "UserHandler.h"
#include "Database.h"

int main(int argc, char *argv[])
{
        std::cout << "Server started" << std::endl;
        DatabaseHandler::deleteAccount("testqwe");
        DatabaseHandler::createAccount("louis3", "password");
        DatabaseHandler::checkLogin("louis3", "password");
//        UserHub userHub;
//        LandingPool entryDoor {12345, userHub};
//        return entryDoor.openToConnections();
}
