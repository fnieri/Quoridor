#pragma once

#include <sockpp/tcp_socket.h>

using Socket = sockpp::tcp_socket;

class SocketUser
{
public:
    SocketUser(Socket &&);

    void send(const std::string &);
    std::string receive();

protected:
    Socket m_socket;
};
