#include "ServerController.h"

ServerController::ServerController(MainController *mainController)
{
    // TODO use an external server config (f.e. parameter)
    bridge = std::make_unique<ServerBridge>("localhost", 12346, mainController);

    bridge->startHandling();
}

auto ServerController::sendJson(const json &toSend) -> void
{
    bridge->sendAsync(toSend.dump());
}

auto ServerController::sendSyncJson(const json &toSend) -> json
{
    return json::parse(bridge->getSyncAnswer(toSend.dump()));
}

auto ServerController::login(const std::string &username, const std::string &password) -> bool
{
    auto answer = sendSyncJson(SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, username, password));
    return answer["action"] == toJsonString(ClientAuthAction::LOGIN) && answer["status"] == toJsonString(RequestStatus::SUCCESS);
}

auto ServerController::registerUser(const std::string &username, const std::string &password) -> bool
{
    auto answer = sendSyncJson(SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTRATION, username, password));
    return answer["action"] == toJsonString(ClientAuthAction::REGISTRATION) && answer["status"] == toJsonString(RequestStatus::SUCCESS);
}

auto ServerController::sendFriendMessage(const std::string &sender, const std::string &receiver, const std::string &message) -> void
{
    sendJson(SerializableMessageFactory::serializeFriendMessage(sender, receiver, message));
    fetchFriendMessages(sender, receiver);
}

auto ServerController::sendFriendRequest(const std::string &sender, const std::string &receiver) -> void
{
    sendJson(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, sender, receiver));
}

auto ServerController::acceptFriendRequest(const std::string &sender, const std::string &receiver) -> void
{
    sendJson(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_ACCEPT, sender, receiver));
}

auto ServerController::declineFriendRequest(const std::string &sender, const std::string &receiver) -> void
{
    sendJson(SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REFUSE, sender, receiver));
}

auto ServerController::sendGameMessage(const std::string &sender, std::vector<std::string> &receivers, const std::string &message, int gameID) -> void
{
    sendJson(SerializableMessageFactory::serializeInGameMessage(sender, receivers, message, gameID));
}

auto ServerController::fetchData() -> void
{
    fetchFriends();
    fetchElo();
    fetchLeaderboard();
}

auto ServerController::fetchFriends() -> void
{
    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::FRIENDS_LIST));
}

auto ServerController::fetchLeaderboard() -> void
{
    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD));
}

auto ServerController::fetchFriendRequestsReceived() -> void
{
    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::FRIEND_REQUESTS_RECEIVED));
}

auto ServerController::fetchElo() -> void
{
    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::ELO));
}

auto ServerController::fetchFriendMessages(const std::string &requester, const std::string &receiver) -> void
{
    sendJson(SerializableMessageFactory::serializeFriendChatRequest(requester,receiver));
}
