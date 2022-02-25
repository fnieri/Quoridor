/**
 * @file RequestHandler.cpp
 * @author Boris Petrov
 * @brief Asynchronously read and respond to requests
 * @date 02/25/22
 */

#include "RequestHandler.h"

#include <iostream>
#include <thread>

void RequestHandler::startHandling()
{
    std::thread th {&RequestHandler::threadBridge, this};
    th.detach();
}

void RequestHandler::threadBridge(RequestHandler *handler)
{
    handler->handleRequests();
}

/* RequestHandler::~RequestHandler() noexcept */
/* { */
/*     if (m_thread.joinable()) */
/*         m_thread.join(); */
/* } */
