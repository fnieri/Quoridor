#pragma once

#include <sockpp/tcp_socket.h>

using Socket = sockpp::tcp_socket;

class SocketUser
{
public:
    SocketUser(Socket &&);

    SocketUser(const SocketUser &) = delete;
    SocketUser(SocketUser &&) = default;

    SocketUser &operator=(const SocketUser &) = delete;
    SocketUser &operator=(SocketUser &&) = default;

    void send(const std::string &);
    std::string receive();

protected:
    Socket m_socket;
};
