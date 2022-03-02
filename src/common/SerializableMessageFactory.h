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
    static nlohmann::json serializeUserRequest(ClientAuthAction action, const std::string &username, const std::string &password);

    static nlohmann::json serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn);

    static nlohmann::json serializePawnAction(PlayerAction &pawnAction, int playerID);

    static nlohmann::json serializeWallAction(WallAction &wallAction, int playerID);

    static nlohmann::json serializeInGameMessage(const std::string &sender, std::vector<std::string> &receivers, const std::string &message, int gameID);

    static nlohmann::json serializeFriendMessage(const std::string &sender, const std::string &receiver, const std::string &message);

    static nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, const std::string &username, int ELO);

    static nlohmann::json serializeFriendRequest(FriendAction friendAction, const std::string &friendRequestSender, const std::string &friendRequestReceiver);

    static nlohmann::json serializeFriendRemove(const std::string &friendRemoveSender, const std::string &friendRemoveReceiver);

    static nlohmann::json serializeInGameRelatedRequest(GameAction gameAction, const std::string &username);

    static nlohmann::json serializeRequestExchange(DataType dataType);

    static nlohmann::json serializeAnswerExchange(DataType dataType, nlohmann::json &serializedData);

    static nlohmann::json serializeStatusTransmission(RequestStatus requestStatus);

    static nlohmann::json serializeGameSetup(GameMode gameMode, GameInvite gameInvite, std::vector<std::string> &players);

    static nlohmann::json serializeGameSetup(GameMode gameMode, GameInvite gameInvite, std::vector<std::string> &players, int time, int increment);
};
