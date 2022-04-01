#include "ServerController.h"

#include "src/client/PlayerAction.h"
#include "src/client/WallAction.h"

#include "src/server/Config.h"
#include <nlohmann/json.hpp>

ServerController::ServerController(MainController *mainController)
{
    std::string serverIP = ConfigHandler::Instance()->getClientProperty(ClientProperty::SERVER_IP);
    int serverPort = std::stoi(ConfigHandler::Instance()->getClientProperty(ClientProperty::PORT));
    bridge = std::make_unique<ServerBridge>(serverIP, serverPort, mainController);
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
    fetchFriendRequestsReceived();
    fetchFriendRequestsSent();
    fetchGameIds();
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

auto ServerController::fetchFriendRequestsSent() -> void
{
    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::FRIEND_REQUESTS_SENT));
}

auto ServerController::fetchElo() -> void
{
    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::ELO));
}

auto ServerController::fetchFriendMessages(const std::string &requester, const std::string &receiver) -> void
{
    sendJson(SerializableMessageFactory::serializeFriendChatRequest(requester, receiver));
}

auto ServerController::fetchGameIds() -> void
{
    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::GAME_IDS));
}

auto ServerController::removeFriend(const std::string &sender, const std::string &receiver) -> void
{
    sendJson(SerializableMessageFactory::serializeFriendRemove(sender, receiver));
}

auto ServerController::createGame(const std::string &username, const std::vector<std::string> &players) -> void
{
    auto gamePlayers = players;
    gamePlayers.push_back(username);
    GameModel defaultGameModel {gamePlayers};
    sendJson(
        SerializableMessageFactory::serializeGameCreationRequest(username, const_cast<std::vector<std::string> &>(players), defaultGameModel.serialized()));
}

auto ServerController::isConnected() const -> bool
{
    return bridge->isConnected();
}

auto ServerController::joinGame(const int &gameId, const std::string &username) -> void
{
    sendJson(SerializableMessageFactory::serializeGameParticipationRequest(GameSetup::JOIN_GAME, gameId, username));
}

auto ServerController::quitGame(const int &gameId, const std::string &username) -> void
{
    sendJson(SerializableMessageFactory::serializeGameParticipationRequest(GameSetup::QUIT_GAME, gameId, username));
}

auto ServerController::playPlayerAction(PlayerAction action, const int &playerIdx) -> void
{
    sendJson(SerializableMessageFactory::serializePawnAction(action, playerIdx));
}

auto ServerController::playWallAction(WallAction action, const int &playerIdx) -> void
{
    sendJson(SerializableMessageFactory::serializeWallAction(action, playerIdx));
}

auto ServerController::surrend(const std::string &username) -> void
{
    sendJson(SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::SURRENDER, username));
}

auto ServerController::fetchGameMessages(int) -> void
{
//    sendJson(SerializableMessageFactory::serializeRequestExchange(DataType::));
}
