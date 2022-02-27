#pragma once

#include <nlohmann/json.hpp>

#include "AuthSerializableMessageFactory.h"
#include "BoardActionsSerializableMessageFactory.h"
#include "ChatBoxSerializableMessageFactory.h"
#include "FriendActionsSerializableMessageFactory.h"
#include "GameRelatedActionsSerializableMessageFactory.h"
#include "MessageEnums/Actions/AuthActions.h"
#include "MessageEnums/Actions/ChatBoxActions.h"
#include "MessageEnums/Actions/FriendActions.h"
#include "MessageEnums/Actions/GameActions.h"
#include "MessageEnums/Actions/ObjectExchanges.h"
#include "MessageEnums/Actions/PlayerActions.h"
#include "MessageEnums/DataTypes.h"
#include "MessageEnums/Modes/GameModes.h"
#include "MessageEnums/Status.h"
#include "ObjectExchangesSerializableMessageFactory.h"
#include "Serializable.h"

class SerializableMessageFactory
{
public:
    static nlohmann::json serializeUserRequest(ClientAuthAction action, std::string username, std::string password);

    static nlohmann::json serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn);

    static nlohmann::json serializePawnAction(PlayerAction pawnAction, int playerID);

    static nlohmann::json serializeWallAction(WallAction wallAction, int playerID);

    static nlohmann::json serializeUserChatBoxRequest(ChatInteraction interaction, int chatboxID, std::string username, std::string message, int timestamp);

    static nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::string username);

    static nlohmann::json serializeFriendRequest(FriendAction friendAction, std::string friendRequestSender, std::string friendRequestReceiver);

    static nlohmann::json serializeFriendRemove(std::string friendRemoveSender, std::string friendRemoveReceiver);

    static nlohmann::json serializeInGameRequest(GameAction gameAction, std::string username);

    static nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::string username, int ELO);

    static nlohmann::json serializeGameRelatedRequest(GameAction gameAction, std::string username);

    static nlohmann::json serializeRequestExchange(DataType dataType);

    static nlohmann::json serializeAnswerExchange(Exchange answerExchange, DataType dataType, Serializable serializableData);

    static nlohmann::json serializeStatusTransmission(RequestStatus requestStatus);
};