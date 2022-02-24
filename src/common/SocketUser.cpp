#include "SocketUser.h"

#include "Exceptions.h"

#include <iostream>

// TODO: be more thorough with error handling...
// TODO: add ability to wait for activity on one socket > avoid blocking reads

SocketUser::SocketUser(Socket &&socket)
    : m_socket {std::move(socket)}
{
}

void SocketUser::send(const std::string &msg)
{
    std::lock_guard<std::mutex> guard {m_socketMutex};

    auto sz {msg.size()};
    if (m_socket.write_n(&sz, sizeof(sz)) < sizeof(sz))
        throw UnableToSend {};

    if (m_socket.write_n(msg.c_str(), sz) < sz)
        throw UnableToSend {};
}

std::string SocketUser::receive()
{
    std::lock_guard<std::mutex> guard {m_socketMutex};

    ssize_t sz {0};
    if (m_socket.read_n(&sz, sizeof(sz)) < sizeof(sz))
        throw UnableToRead {};

    auto buff = new char[sz];
    if (m_socket.read_n(buff, sz) < sz)
        throw UnableToRead {};

    std::string ret {buff};
    delete[] buff;

    return ret;
}
