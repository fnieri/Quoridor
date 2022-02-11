/**
 * @author Boris Petrov
 */

#include "LandingPool.h"

#include <iostream>

LandingPool::LandingPool(in_port_t port, LoginHub &loginHub)
    : m_acceptor {port}
    , m_loginHub {loginHub}
{
}

int LandingPool::openToConnections()
{
    while (true) {
        sockpp::tcp_socket new_client {m_acceptor.accept()};

        if (!new_client) {
            std::cerr << "Error while accepting new connection: " << new_client.last_error_str() << std::endl;

        } else {
            m_loginHub.addClient(std::move(newClient));
        }
    }

    return 0;
}
