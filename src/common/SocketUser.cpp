#include "SocketUser.h"

#include "Exceptions.h"

#include <iostream>
#include <sys/select.h>

// TODO: be more thorough with error handling...

SocketUser::SocketUser(Socket &&socket)
    : m_socket {std::move(socket)}
{
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
