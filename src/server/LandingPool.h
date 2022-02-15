/**
 * @author Boris Petrov
 */

#pragma once

#include "UserHandler.h"

#include <sockpp/tcp_acceptor.h>

/**
 * New connections will land here and are assigned
 * to a personnal handler.
 */
class LandingPool
{
public:
    LandingPool(in_port_t, UserHub &);

    int openToConnections();

private:
    sockpp::tcp_acceptor m_acceptor;
    UserHub &m_userHub;
};
