/**
 * @author Boris Petrov
 */

#pragma once

#include "UserHandler.h"

#include <sockpp/tcp_acceptor.h>

/**
 * First contact with the holy server
 *
 * New connections will land here and be assigned
 * to a personnal handlers which will receive their requests
 * and respond accordingly.
 *
 * @param port from where new connections will arrive
 * @param userHub where they'll be sent
 *
 * @see UserHandler
 */
class LandingPool
{
public:
    LandingPool(in_port_t, UserHub &);

    /**
     * Start accepting new clients
     *
     * Open the port supplied in the class creation
     * and assign new connections to their own, private
     * handlers.
     */
    int openToConnections();

private:
    sockpp::tcp_acceptor m_acceptor;
    UserHub &m_userHub;
};
