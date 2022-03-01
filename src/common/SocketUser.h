/**
 * @file SocketUser.h
 * @author Boris Petrov
 * @brief Facility to send and receive strings
 * @date 02/25/22
 */

#pragma once

#include <sockpp/tcp_socket.h>

#include <mutex>

using Socket = sockpp::tcp_socket;

/**
 * Facility to send and receive strings over socket
 *
 * @note The class should be thread safe.
 */
class SocketUser
{
public:
    SocketUser(Socket && = Socket {});

    SocketUser(const SocketUser &) = delete;
    SocketUser(SocketUser &&) = default;

    SocketUser &operator=(const SocketUser &) = delete;
    SocketUser &operator=(SocketUser &&) = default;

    void setSocket(Socket &&);
    bool isOpen() const;
    void close();
    /**
     * Write a std::string in the socket
     *
     * @param message string to be sent
     */
    void send(const std::string &);
    /**
     * Read a std::string from the socket
     *
     * @return message string read
     */
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
