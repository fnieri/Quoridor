/**
 * @author Boris Petrov
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
    while (m_isServerOpen) {
        sockpp::tcp_socket newClient {m_acceptor.accept()};

        if (!newClient) {
            std::cerr << "Error while accepting new connection: " << newClient.last_error_str() << std::endl;

        } else {
            m_userHub.add(std::move(newClient));
        }
    }

    return 0;
}

void LandingPool::close()
{
    m_isServerOpen = false;
}
