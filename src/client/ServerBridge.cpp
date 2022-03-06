#include "ServerBridge.h"

#include "src/common/Exceptions.h"

#include <thread>

ServerBridge::ServerBridge(const std::string &address, int16_t port)
{
    sockpp::tcp_connector connector;
    connector.connect(sockpp::inet_address(address, port));
    setSocket(std::move(connector));
}

void ServerBridge::handleRequests()
{
    while (isOpen()) {
        try {
            if (hasReadActivity(1)) {
                auto serRequest {receive()};

                // Do not continue if the thread was terminated during or after the receive
                if (!isOpen())
                    break;

                /* std::thread th {&ServerController::processRequest, m_serverController, serRequest}; */
                /* th.detach(); */
            }
        }
        // Client was disconnected
        catch (UnableToRead &) {
            if (!isOpen())
                close();
        } catch (UnableToSend &) {
            if (!isOpen())
                close();
        }
    }
}

void ServerBridge::sendAsync(const std::string& serRequest)
{
    send(serRequest);
}