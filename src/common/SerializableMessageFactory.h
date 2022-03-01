#pragma once

#include <nlohmann/json.hpp>

#include "AuthSerializableMessageFactory.h"
#include "BoardActionsSerializableMessageFactory.h"
#include "ChatBoxSerializableMessageFactory.h"
#include "FriendActionsSerializableMessageFactory.h"
#include "GameRelatedActionsSerializableMessageFactory.h"
#include "GameSetupSerializableMessageFactory.h"
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
    static nlohmann::json serializeUserRequest(ClientAuthAction action, std::string& username, std::string& password);

    static nlohmann::json serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn);

    static nlohmann::json serializePawnAction(PlayerAction& pawnAction, int playerID);

    static nlohmann::json serializeWallAction(WallAction& wallAction, int playerID);

    static nlohmann::json serializeInGameMessage(std::string& sender, std::vector<std::string>& receivers, std::string& message, int gameID);

    static nlohmann::json serializeFriendMessage(std::string& sender, std::string& receiver, std::string& message);

    static nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, std::string& username, int ELO);

    static nlohmann::json serializeFriendRequest(FriendAction friendAction, std::string& friendRequestSender, std::string& friendRequestReceiver);

    static nlohmann::json serializeFriendRemove(std::string& friendRemoveSender, std::string& friendRemoveReceiver);

    static nlohmann::json serializeInGameRelatedRequest(GameAction gameAction, std::string& username);

    static nlohmann::json serializeRequestExchange(DataType dataType, Serializable& serializable);

    static nlohmann::json serializeAnswerExchange(DataType dataType, Serializable& serializableData);

    static nlohmann::json serializeStatusTransmission(RequestStatus requestStatus);

    static nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string>& players);

    static nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string>& players, int time, int increment);

};
