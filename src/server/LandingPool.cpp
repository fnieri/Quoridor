/**
 * @file LandingPool.cpp
 * @author Boris Petrov
 * @brief Entry door to the server
 * @date 02/25/22
 */

#include "LandingPool.h"

#include <iostream>

LandingPool::LandingPool(in_port_t port, UserHub &userHub)
    : m_acceptor {port}
    , m_userHub {userHub}
{
}

int LandingPool::openToConnections()
{
    while (m_acceptor.is_open()) {
        sockpp::tcp_socket newClient {m_acceptor.accept()};

        if (!m_acceptor.is_open()) {
            break;

        } else if (!newClient) {
            std::cerr << " Error while accepting new connection: " << newClient.last_error_str() << std::endl;

        } else {
            m_userHub.add(std::move(newClient));
        }
    }

    return 0;
}

void LandingPool::close()
{
    m_acceptor.close();
}
