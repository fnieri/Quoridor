#include "SocketUser.h"

#include "Exceptions.h"

SocketUser::SocketUser(Socket &&socket)
    : m_socket {socket}
{
}

void SocketUser::send(const std::string &msg)
{
    auto sz {msg.size()};

    if (m_socket.write_n(&sz, sizeof(sz)) == -1)
        throw UnableToSend {};

    if (m_socket.write_n(sz, msg.c_str()) == -1)
        throw UnableToSend {};
}

std::string SocketUser::receive()
{
    ssize_t sz;
    if (m_socket.read_n(&sz, sizeof(sz)) == -1)
        throw UnableToRead {};

    auto buff = new char[sz];
    if (m_socket.read_n(buff, sz) == -1)
        throw UnableToRead {};

    std::string ret {buff};
    delete[] buff;

    return ret;
}
