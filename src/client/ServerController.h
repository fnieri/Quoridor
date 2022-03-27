#pragma once

#include "src/client/MainController.h"
#include "src/client/ServerBridge.h"
#include "src/common/SerializableMessageFactory.h"

#include <nlohmann/json_fwd.hpp>

class ServerController
{
    std::unique_ptr<ServerBridge> bridge;

public:
    explicit ServerController(MainController *);
    auto sendJson(const json &) -> void;
    auto sendSyncJson(const json &) -> json;

    auto login(const std::string &username, const std::string &password) -> bool;
    auto registerUser(const std::string &username, const std::string &password) -> bool;

    auto joinGame(const int &gameId) -> void;
    auto sendGameMessage(const std::string &sender, std::vector<std::string> &receivers, const std::string &message, int gameID) -> void;

    auto sendFriendMessage(const std::string &sender, const std::string &receiver, const std::string &message) -> void;
    auto sendFriendRequest(const std::string &sender, const std::string &receiver) -> void;
    auto acceptFriendRequest(const std::string &sender, const std::string &receiver) -> void;
    auto declineFriendRequest(const std::string &sender, const std::string &receiver) -> void;
    auto removeFriend(const std::string &sender, const std::string &receiver) -> void;

    auto fetchData() -> void;
    auto fetchFriends() -> void;
    auto fetchFriendRequestsReceived() -> void;
    auto fetchGameIds() -> void;
    auto fetchGameMessages(int) -> void;
    auto fetchFriendMessages(const std::string &requester, const std::string &receiver) -> void;
    auto fetchLeaderboard() -> void;
    auto fetchElo() -> void;

    auto createGame(const std::string &username, const std::vector<std::string> &players) -> void;
};
