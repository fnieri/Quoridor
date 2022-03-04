/**
 * @file ServerBridge.h
 * @author Boris Petrov
 * @brief Way to communicate with the server from the client
 * @date 02/25/22
 */

#pragma once

#include "src/common/RequestHandler.h"

#include <sockpp/tcp_connector.h>

class ServerBridge : public RequestHandler
{
public:
    /**
     * @param address the ip address of the server
     * @param port the port on which to connect
     */
    ServerBridge(const std::string &, int16_t);

private:
    /* SeverController *m_serverController; */

    void handleRequests() override;
};
