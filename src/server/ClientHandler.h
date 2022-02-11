#pragma once

#include <sockpp/tcp_acceptor.h>

#include <memory>

class ClientHandler
{
protected:
    std::shared_ptr<User> m_user;

public:
    ClientHandler(sockpp::tcp_socket);

    /**
     * Every message a client sends to the server will be
     * processed by its own handler, be it for the ChatBox,
     * a Game or the Login.
     *
     * The message received by the handler is analyzed and
     * transferred to the appropriate specific handler (e.g
     * LoginHangler, GameHandler, etc).
     *
     *                          LoginHandler
     *                        /
     * Client -- ClientHandler
     *                        \ GameHandler
     */
    void readRequests();
};
