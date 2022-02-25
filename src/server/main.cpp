/**
 * @file main.cpp
 * @author Boris Petrov
 * @brief Server's main
 * @date 02/25/22
 */

#include "LandingPool.h"
#include "UserHandler.h"

int main(int argc, char *argv[])
{
    UserHub userHub;
    LandingPool entryDoor {12345, userHub};
    return entryDoor.openToConnections();
}
