#include <catch2/catch.hpp>

#include "src/common/SocketUser.h"

#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>

#include <thread>

class DummyWriter
{
private:
    SocketUser *m_sockUser {nullptr};
    int16_t m_port;

public:
    DummyWriter(int16_t port = 12345)
        : m_port {port}
    {
    }

    void connect()
    {
        sockpp::tcp_connector connector;
        connector.connect(sockpp::inet_address("localhost", m_port));
        m_sockUser = new SocketUser {std::move(connector)};
    }

    void send(const std::string &msg)
    {
        m_sockUser->send(msg);
    }
};

class DummyReader
{
private:
    SocketUser *m_sockUser {nullptr};
    in_port_t m_port;

public:
    DummyReader(in_port_t port = 12345)
        : m_port {port}
    {
    }

    void open()
    {
        sockpp::tcp_acceptor acceptor {m_port};
        m_sockUser = new SocketUser {acceptor.accept()};
    }

    std::string receive()
    {
        return m_sockUser->receive();
    }

    bool hasActivity(time_t s)
    {
        return m_sockUser->hasReadActivity(s);
    }
};

void delayWrite(DummyWriter *dwr, const std::string &msg, time_t delay)
{
    sleep(delay);
    dwr->send(msg);
}

SCENARIO("Test SocketUser")
{
    DummyReader rd;
    DummyWriter wr;

    std::thread th {&DummyReader::open, &rd};
    wr.connect();
    if (th.joinable())
        th.join();

    GIVEN("Writing and receiving")
    {
        auto toSend {"Test 01"};

        std::thread write {&DummyWriter::send, &wr, toSend};
        auto msg {rd.receive()};
        if (write.joinable())
            write.join();

        REQUIRE(msg == toSend);
    }

    GIVEN("Wait for activity")
    {
        std::string res1 {};
        std::string res2 {};
        std::thread write {delayWrite, &wr, "Test 02", 2};

        // Should not pass
        if (rd.hasActivity(1)) {
            res1 = rd.receive();
        }

        // Should pass
        if (rd.hasActivity(2)) {
            res2 = rd.receive();
        }

        if (write.joinable())
            write.join();

        REQUIRE(res1 == "");
        REQUIRE(res2 == "Test 02");
    }
}
