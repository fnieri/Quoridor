#include "SerializableMessageFactory.h"

using json = nlohmann::json;

json SerializableMessageFactory::serializeUserRequest(ClientAuthAction action, std::string username, std::string password)
{
    return AuthSerializableMessageFactory::serializeUserRequest(action, username, password);
}

json SerializableMessageFactory::serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn)
{
    return AuthSerializableMessageFactory::serializeServerAnswer(action, status, authReturn);
}

json SerializableMessageFactory::serializePawnAction(PlayerAction pawnAction, int playerID)
{
    return BoardActionsSerializableMessageFactory::serializePawnAction(pawnAction, playerID);
}

json SerializableMessageFactory::serializeWallAction(WallAction wallAction, int playerID)
{
    return BoardActionsSerializableMessageFactory::serializeWallAction(wallAction, playerID);
}

json serializeFriendRequest(FriendAction friendAction, std::string friendRequestSender, std::string friendRequestReceiver)
{
    return FriendActionsSerializableMessageFactory::serializeFriendRequest(friendAction, friendRequestSender, friendRequestReceiver);
}

json serializeFriendRemove(std::string friendRemoveSender, std::string friendRemoveReceiver)
{
    return FriendActionsSerializableMessageFactory::serializeFriendRemove(friendRemoveSender, friendRemoveReceiver);
}

json SerializableMessageFactory::serializeUserChatBoxRequest(
    ChatInteraction interaction, int chatboxID, std::string username, std::string message, int timestamp)
{
    return ChatBoxSerializableMessageFactory::serializeUserChatBoxRequest(interaction, chatboxID, username, message, timestamp);
}

json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::string username, int ELO)
{
    return GameRelatedActionsSerializableMessageFactory::serializeQueueJoinRequest(queueAction, gameMode, username, ELO);
}

json serializeGameRelatedRequest(GameAction gameAction, std::string username)
{
    return GameRelatedActionsSerializableMessageFactory::serializeGameRelatedRequest(gameAction, username);
}

json serializeRequestExchange(DataType dataType)
{
    return ObjectExchangesSerializableMessageFactory::serializeRequestExchange(dataType);
}

json serializeAnswerExchange(Exchange answerExchange, DataType dataType, Serializable serializableData)
{
    return ObjectExchangesSerializableMessageFactory::serializeAnswerExchange(answerExchange, dataType, serializableData);
}

json serializeStatusTransmission(RequestStatus requestStatus)
{
    return ObjectExchangesSerializableMessageFactory::serializeStatusTransmission(requestStatus);
}