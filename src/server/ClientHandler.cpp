#include "ClientHandler.h"

/* class SocketCommunicator */
/* { */
/*     public: */
/*         ssize_t sendString(sockpp::tcp_socket, const std::string &); */
/*         std::string receiveString(sockpp::tcp_socket); */
/* }; */

ClientHandler::ClientHandler(sockpp::tcp_socket clientSocket)
    : m_user {std::make_shared(clientSocket)}
{
}

void ClientHandler::readRequests()
{
    auto stillConnected {true};

    while (stillConnected) { }
}
