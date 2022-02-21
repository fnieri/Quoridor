/**
 * @author Boris Petrov
 */

#pragma once

#include "src/common/SocketUser.h"

#include <thread>

/**
 * Facility to run method in a thread
 *
 * For the purpose of this project, this threaded method is the
 * handling of requests, i.e. reading messages from a socket.
 *
 * @warning Instances of this class *must* be moved because of
 * the presence of a socket. If copied, errors will be reported.
 */
class RequestHandler : public SocketUser
{
public:
    using SocketUser::SocketUser;

    RequestHandler(const RequestHandler &) = delete;
    RequestHandler(RequestHandler &&) = default;

    RequestHandler &operator=(const RequestHandler &) = delete;
    RequestHandler &operator=(RequestHandler &&) = default;

    /**
     * Create a thread with handleRequests
     *
     * @see handleRequests
     */
    virtual void startHandling();
    virtual ~RequestHandler() noexcept;

protected:
    std::thread m_thread;
    /**
     * Method running in its thread
     */
    virtual void handleRequests() = 0;

private:
    /**
     * Allow calling threaded virtual methods.
     *
     * @note This is necessary because a thread must have
     * a known pointer to a function. Thus, it can't call
     * virtual methods which are resolved during run-time.
     * It can be a static one for example, as it is in
     * this case.
     *
     * @note This is only a bridge, the main method (virtual)
     * is called from this one.
     */
    static void threadBridge(RequestHandler *);
};
