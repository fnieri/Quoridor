/**
 * @file ServerBridge.h
 * @author Boris Petrov
 * @brief Way to communicate with the server from the client
 * @date 02/25/22
 */

#pragma once

#include "src/client/MainController.h"
#include "src/common/Observer.h"
#include "src/common/RequestHandler.h"

#include <sockpp/tcp_connector.h>

class MainController;

class ServerBridge : public RequestHandler
{
private:
    /* SeverController *m_serverController; */
    MainController *m_mainController;

    bool m_isExchangingSynchronously;
    std::mutex m_receivingMutex;

    void handleRequests() override;

public:
    /**
     * @param address the ip address of the server
     * @param port the port on which to connect
     */
    ServerBridge(const std::string &, int16_t, MainController *);

    /**
     * @param serRequest request to send to the server
     *
     * @note No immediate answer should be expected as this is asynchronously.
     */
    void sendAsync(const std::string &);

    std::string getSyncAnswer(const std::string &);
};
