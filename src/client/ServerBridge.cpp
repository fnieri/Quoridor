#include "ServerBridge.h"

#include "src/common/Exceptions.h"

#include <thread>

ServerBridge::ServerBridge(const std::string &address, int16_t port, MainController *controller)
    : m_mainController(controller)
{
    sockpp::tcp_connector connector;
    connector.connect(sockpp::inet_address(address, port));
    setSocket(std::move(connector));
}

std::string ServerBridge::getSyncAnswer(const std::string &serRequest)
{
    m_isExchangingSynchronously = true;
    std::lock_guard<std::mutex> guard {m_receivingMutex};

    send(serRequest);
    auto answer {receive()};

    m_mainController->processRequest(answer);

    m_isExchangingSynchronously = false;

    return answer;
}

void ServerBridge::handleRequests()
{
    while (isOpen()) {
        try {
            if (hasReadActivity(1)) {
                // Wait until the sync request is done
                if (m_isExchangingSynchronously) {
                    std::lock_guard<std::mutex> guard {m_receivingMutex};

                    // If not expecting sync answer, accept the async one
                } else {

                    auto serRequest {receive()};

                    // Do not continue if the thread was terminated during or after the receive
                    if (!isOpen())
                        break;

                    std::thread th {&MainController::processRequest, m_mainController, serRequest};
                    th.detach();
                }
            }
        }
        // Client was disconnected
        // TODO maybe exit client ?
        catch (UnableToRead &) {
            if (!isOpen())
                close();
        } catch (UnableToSend &) {
            if (!isOpen())
                close();
        }
    }
}

void ServerBridge::sendAsync(const std::string &serRequest)
{
    send(serRequest);
}

bool ServerBridge::isConnected() const
{
    return isOpen();
}
