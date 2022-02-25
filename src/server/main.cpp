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
//        DatabaseHandler::createAccount("louis4", "password");
//        DatabaseHandler::sendMessage("louis4", "fuck you", 12);
//        DatabaseHandler::isGameIdUsed(13);
        std::cout << "getting messages louis4" << std::endl;
        std::vector<std::vector<std::string>> mes = DatabaseHandler::getMessages("louis4", "louis6");
        for (auto i : mes)
        {
            std::cout << i[0] << ": " << i[1] << std::endl;
        }
//        DatabaseHandler::sendMessage("louis3", "louis4", "Hello");
//        UserHub userHub;
//        LandingPool entryDoor {12345, userHub};
//        return entryDoor.openToConnections();
}
