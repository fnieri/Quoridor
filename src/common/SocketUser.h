#pragma once

#include <sockpp/tcp_socket.h>

#include <mutex>

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

    /**
     * Blocking call until activity appears on the socket
     *
     * @note This allows to wait for input without actually
     * reading the socket (which is blocking for the writing).
     * Here's an example:
     *
     * ```cpp
     * if (hasActivity(1))
     *     auto msg {receive()};
     * ```
     */
    bool hasReadActivity(time_t);

protected:
    Socket m_socket;
    std::mutex m_socketMutex;
};
