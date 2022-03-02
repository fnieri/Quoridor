#include "SerializableMessageFactory.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json SerializableMessageFactory::serializeUserRequest(ClientAuthAction action, std::string &username, std::string &password)
{
    return AuthSerializableMessageFactory::serializeUserRequest(action, username, password);
}

json SerializableMessageFactory::serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn)
{
    return AuthSerializableMessageFactory::serializeServerAnswer(action, status, authReturn);
}

json SerializableMessageFactory::serializePawnAction(PlayerAction &pawnAction, int playerID)
{
    return BoardActionsSerializableMessageFactory::serializePawnAction(pawnAction, playerID);
}

json SerializableMessageFactory::serializeWallAction(WallAction &wallAction, int playerID)
{
    return BoardActionsSerializableMessageFactory::serializeWallAction(wallAction, playerID);
}

json SerializableMessageFactory::serializeFriendRequest(FriendAction friendAction, std::string &friendRequestSender, std::string &friendRequestReceiver)
{
    return FriendActionsSerializableMessageFactory::serializeFriendRequest(friendAction, friendRequestSender, friendRequestReceiver);
}

json SerializableMessageFactory::serializeFriendRemove(std::string &friendRemoveSender, std::string &friendRemoveReceiver)
{
    return FriendActionsSerializableMessageFactory::serializeFriendRemove(friendRemoveSender, friendRemoveReceiver);
}

json SerializableMessageFactory::serializeInGameMessage(std::string &sender, std::vector<std::string> &receivers, std::string &message, int gameID)
{
    return ChatBoxSerializableMessageFactory::serializeInGameMessage(sender, receivers, message, gameID);
}

json SerializableMessageFactory::serializeFriendMessage(std::string &sender, std::string &receiver, std::string &message)
{
    return ChatBoxSerializableMessageFactory::serializeFriendMessage(sender, receiver, message);
}

json SerializableMessageFactory::serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::string &username, int ELO)
{
    return GameRelatedActionsSerializableMessageFactory::serializeQueueJoinRequest(queueAction, gameMode, username, ELO);
}

json SerializableMessageFactory::serializeInGameRelatedRequest(GameAction gameAction, std::string &username)
{
    return GameRelatedActionsSerializableMessageFactory::serializeInGameRelatedRequest(gameAction, username);
}

json SerializableMessageFactory::serializeRequestExchange(DataType dataType)
{
    return ObjectExchangesSerializableMessageFactory::serializeRequestExchange(dataType);
}

json SerializableMessageFactory::serializeAnswerExchange(DataType dataType, json& serializedData)
{
    return ObjectExchangesSerializableMessageFactory::serializeAnswerExchange(dataType, serializedData);
}

json SerializableMessageFactory::serializeStatusTransmission(RequestStatus requestStatus)
{
    return ObjectExchangesSerializableMessageFactory::serializeStatusTransmission(requestStatus);
}

json SerializableMessageFactory::serializeGameSetup(GameMode gameMode, GameInvite gameInvite, std::vector<std::string> &players)
{
    return GameSetupSerializableMessageFactory::serializeGameSetup(gameMode, gameInvite, players);
}

json SerializableMessageFactory::serializeGameSetup(GameMode gameMode, GameInvite gameInvite, std::vector<std::string> &players, int time, int increment)
{
    return GameSetupSerializableMessageFactory::serializeGameSetup(gameMode, gameInvite, players, time, increment);
}
