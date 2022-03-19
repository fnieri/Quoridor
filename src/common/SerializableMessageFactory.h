/**
 * @brief Methods in this class will call other classes to do their tasks
 * This is done to group all methods in one class to ease black-box reuse
 * @author Francesco Nieri
 * @date 04/03/21
 */

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
#include "MessageEnums/Domain.h"
#include "MessageEnums/Modes/GameModes.h"
#include "MessageEnums/Status.h"
#include "ObjectExchangesSerializableMessageFactory.h"
#include "Serializable.h"

class SerializableMessageFactory
{
public:
    /*----------------------
     * Auth
     *-----------------------*/
    /**
     * Look in SerializableMessageFactory for explanation
     */
    static nlohmann::json serializeUserRequest(ClientAuthAction action, const std::string &username, const std::string &password);
    /**
     * Look in SerializableMessageFactory for explanation
     */
    static nlohmann::json serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn, const std::string& username);
    /*---------------------
     * BoardActions
     *---------------------*/
    /**
     * Look in BoardActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializePawnAction(PlayerAction &pawnAction, int playerID);
    /**
     * Look in BoardActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeWallAction(WallAction &wallAction, int playerID);
    /*----------------------
     * ChatBox
     *--------------------*/
    /**
     * Look in ChatBoxSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeInGameMessage(const std::string &sender, std::vector<std::string> &receivers, const std::string &message, int gameID);
    /**
     * Look in ChatBoxSerializableMessageFactory for explanation
     */

    static nlohmann::json serializeFriendMessage(const std::string &sender, const std::string &receiver, const std::string &message);

    /*---------------------
     * FriendActions
     *---------------------*/
    /**
     * Look in FriendActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeFriendRequest(FriendAction friendAction, const std::string &friendRequestSender, const std::string &friendRequestReceiver);
    /**
     * Look in FriendActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeFriendRemove(const std::string &friendRemoveSender, const std::string &friendRemoveReceiver);
    /*---------------------
     * GameRelated
     *-------------------*/
    /**
     * Look in GameRelatedActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeInGameRelatedRequest(GameAction gameAction, const std::string &username);
    /**
     * Look in GameRelatedActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeQueueJoinRequest(QueueAction queueAction, GameMode gameMode, const std::string &username, int ELO);
    /**
     * Look in GameRelatedActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeGameStarted(int gameID, nlohmann::json configuration);
    /**
     * Look in GameRelatedActionsSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeGameEnded(int gameID);
    /*------------------
     * ObjectExchanges
     *--------------------*/
    /**
     * Look in ObjectExchangesSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeRequestExchange(DataType dataType);
    /**
     * Look in ObjectExchangesSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeAnswerExchange(DataType dataType, nlohmann::json &serializedData);
    /**
     * Look in ObjectExchangesSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeStatusTransmission(RequestStatus requestStatus);
    /**
     * Look in ObjectExchangesSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeFriendChatRequest(const std::string &requester, const std::string &receiver);
    /**
     * Look in ObjectExchangesSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeRequestGameID(int gameID);
    /*-------------------
     *  GameSetup
     *------------------*/
    /**
     * Look in GameSetupSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string> &players);
    /**
     * Look in GameSetupSerializableMessageFactory for explanation
     */
    static nlohmann::json serializeGameParticipationRequest(GameSetup gameSetup, int gameID);
    /**
     * Look in GameSetupSerializableMessageFactory   for explanation
     */
    static nlohmann::json serializeGameCreationRequest(const std::string &sender, std::vector<std::string> &receivers, nlohmann::json configuration);
};
