/**
 * @file MainController.h
 * @author Boris Petrov
 * @brief Way to communicate with the server from the client
 * @date 02/25/22
 */

#pragma once

#include "src/common/Observer.h"
#include "src/common/RequestHandler.h"

#include <sockpp/tcp_connector.h>

#include <queue>

class MainController : public RequestHandler, public Subject
{
private:
    std::queue<std::string> m_lastRequests;

    bool m_isExchangingSynchronously;
    std::mutex m_receivingMutex;

    std::mutex m_lastReqMutex;

    void handleRequests() override;

public:
    /**
     * @param address the ip address of the server
     * @param port the port on which to connect
     */
    MainController(const std::string &, int16_t);

    /**
     * @param serRequest request to send to the server
     * @returns the answer to that request
     *
     * @note The user of this method should make
     * sure that the request sent to the server will return
     * answer immediately.
     *
     * Current sync requests are:
     * - auth actions (register, login);
     * - resource request (friend_list, friend_requests_sent, friend_requests_received,
     * elo, leaderboard, game_ids);
     *
     * @warning Sending a non-sync request is undefined behaviour!
     */
    std::string getSyncAnswer(const std::string &);

    /**
     * @param serRequest request to send to the server
     *
     * @note No immediate answer should be expected.
     */
    void sendAsync(const std::string &);

    /**
     * @returns the last request received from the server.
     *
     * The async request that can be received are: board actions (wall_action,
     * pawn_action), in game actions (game_started, game_ended), game setup (
     * game_creation) and chat (in_game_chat, friend_chat).
     */
    std::string getLastAsyncRequest();
};
