/**
 * @author Boris Petrov
 */

#include "RequestHandler.h"

#include <thread>

void RequestHandler::startHandling()
{
    m_thread = std::thread {threadBridge, this};
}

void RequestHandler::threadBridge(RequestHandler *handler)
{
    handler->handleRequests();
}

RequestHandler::~RequestHandler() noexcept
{
    m_thread.join();
}
