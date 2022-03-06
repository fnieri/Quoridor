#include "MainController.h"

#include "src/common/Exceptions.h"
#include "src/common/Observer.h"
#include "src/common/QuoridorEvent.h"

#include <iostream>
#include <thread>

std::string MainController::getSyncAnswer(const std::string &serRequest)
{
    m_isExchangingSynchronously = true;
    std::lock_guard<std::mutex> guard {m_receivingMutex};

    send(serRequest);
    auto answer {receive()};

    m_isExchangingSynchronously = false;

    return answer;
}

void MainController::sendAsync(const std::string &serRequest)
{
    send(serRequest);
}

MainController::MainController(const std::string &address, int16_t port)
{
    sockpp::tcp_connector connector;
    connector.connect(sockpp::inet_address(address, port));
    setSocket(std::move(connector));
}

void MainController::handleRequests()
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

                    m_lastReqMutex.lock();
                    m_lastRequests.push(serRequest);
                    m_lastReqMutex.unlock();

                    notifyObservers();
                }
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
    system("clear");
    std::cout << "Server not opened" << std::endl;
    exit(1);
}

std::string MainController::getLastAsyncRequest()
{
    std::lock_guard<std::mutex> guard {m_lastReqMutex};

    auto lastReq {m_lastRequests.front()};
    m_lastRequests.pop();

    return lastReq;
}
