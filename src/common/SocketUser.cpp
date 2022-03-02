/**
 * @file SocketUser.cpp
 * @author Boris Petrov
 * @brief Facility to send and receive strings
 * @date 02/25/22
 */

#include "SocketUser.h"

#include "Exceptions.h"

#include <iostream>
#include <sys/select.h>

// TODO: be more thorough with error handling...

SocketUser::SocketUser(Socket &&socket)
    : m_socket {std::move(socket)}
{
}

void SocketUser::setSocket(Socket &&socket)
{
    m_socket = std::move(socket);
}

bool SocketUser::isOpen() const
{
    return m_socket.is_open();
}

void SocketUser::close()
{
    m_socket.close();
}

bool SocketUser::hasReadActivity(time_t seconds)
{
    fd_set readfd;
    FD_ZERO(&readfd);

    auto sockHandle {m_socket.handle()};
    struct timeval timeout {
        seconds, 0
    };

    FD_SET(sockHandle, &readfd);
    select(sockHandle + 1, &readfd, NULL, NULL, &timeout);

    return FD_ISSET(sockHandle, &readfd);
}

void SocketUser::send(const std::string &msg)
{
    std::lock_guard<std::mutex> guard {m_socketMutex};

    // Firt send the size of the data to be sent
    auto sz {msg.size() + 1};
    if (m_socket.write_n(&sz, sizeof(sz)) < sizeof(sz))
        throw UnableToSend {};

    // Then the data itself
    if (m_socket.write_n(msg.c_str(), sz + 1) < sz + 1)
        throw UnableToSend {};
}

std::string SocketUser::receive()
{
    std::lock_guard<std::mutex> guard {m_socketMutex};

    // First receive the size of the data to be received
    ssize_t sz {0};
    if (m_socket.read_n(&sz, sizeof(sz)) < sizeof(sz))
        throw UnableToRead {};

    // Then the data itself
    auto buff = new char[sz];
    if (m_socket.read_n(buff, sz) < sz)
        throw UnableToRead {};

    std::string ret {buff};
    delete[] buff;

    return ret;
}
