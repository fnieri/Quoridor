/**
 * @author Boris Petrov
 */

#pragma once

#include "src/common/SocketUser.h"

#include <thread>

/**
 * This class gives the possibility to run
 * a method in a threaded way. For the purpose
 * of this project, this threaded method is the
 * handling of requests, i.e. reading messages
 * from a socket.
 */
class RequestHandler : public SocketUser
{
public:
    virtual void startHandling();
    virtual ~RequestHandler() noexcept;

protected:
    std::thread m_thread;
    virtual void handleRequests() = 0;

private:
    // Allow calling threaded virtual methods.
    static void threadBridge(RequestHandler *);
};
