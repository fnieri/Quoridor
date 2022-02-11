/**
 * @author Boris Petrov
 */

#include "LandingPool.h"
#include "LoginHandler.h"

int main(int argc, char *argv[])
{
    /* UserHub userHub; */
    LoginHub loginHub {/*userHub*/};
    LandingPool entryDoor {12345, loginHub};
    return entryDoor.openToConnections();
}
