#include <catch2/catch.hpp>

#include "src/server/LandingPool.h"
#include "src/server/UserHandler.h"
#include <sockpp/tcp_connector.h>

class DummyClient
{
private:
    sockpp::tcp_connector m_connector;
    int16_t m_port;

public:
    DummyClient(int16_t port = 12345)
        : m_port {port}
    {
        m_connector.connect(sockpp::inet_address("localhost", m_port));
    }
};

SCENARIO("Test LandingPool")
{
    UserHub userHub;
    LandingPool landingPool {12345, userHub};

    std::thread th(&LandingPool::openToConnections, &landingPool);
    th.detach();

    GIVEN("Establish connection")
    {
        DummyClient c1[10];
        sleep(1);
        REQUIRE(userHub.connectedUsers() == 10);

        THEN("Connect another client then disconnect it")
        {
            DummyClient c1;
            sleep(1);
            REQUIRE(userHub.connectedUsers() == 11);
        }

        sleep(1);
        REQUIRE(userHub.connectedUsers() == 10);
    }

    landingPool.close();
}
