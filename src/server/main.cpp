/**
 * @author Boris Petrov
 */

#include "LandingPool.h"
#include "UserHandler.h"
#include "ServerUser.h"
#include "Database.h"

int main(int argc, char *argv[])
{
    UserHub userHub;
    LandingPool entryDoor {12345, userHub};
    return entryDoor.openToConnections();
}
