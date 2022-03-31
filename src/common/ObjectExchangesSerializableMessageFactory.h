/**
 * @file ObjectExchangesSerializableMessageFactory.h
 * @brief MessageFactory for requests and answers exchanges between user and server
 * @author Francesco Nieri
 * @date 21/02/2022
 */

#pragma once

#include "MessageEnums/Actions/ObjectExchanges.h"
#include "MessageEnums/DataTypes.h"
#include "MessageEnums/Status.h"
#include "Serializable.h"
#include "nlohmann/json.hpp"
#include <nlohmann/json_fwd.hpp>

template <typename T>
T getResourceFromAnswer(const std::string &serRequest)
{
    nlohmann::json request(nlohmann::json::parse(serRequest));
    nlohmann::json jsonData = request["serialized_data"];
    T data = jsonData.get<T>();

    return data;
}

class ObjectExchangesSerializableMessageFactory
{
public:
    /**
     * @brief serialize a user request of data
     * @param dataType Type of data the user wants to requesto
     * @return json of the request as such
     * {
     * "action" : "object_request",
     * "domain" : "resource_request",
     * "data_type" : "leaderboard | friend_list ...",
     * }
     */
    static nlohmann::json serializeRequestExchange(DataType dataType);
    /**
     * @brief serialize an answer from server to user
     * @param dataType type of data the user has asked
     * @return json of the request as such
     * {
     * "action" : "object_answer",
     * "domain" : "resource_request"
     * "data_type" : "leaderboard | friend_list",
     * "serialized_data" : "json_serialized_object"
     * }
     */
    static nlohmann::json serializeAnswerExchange(DataType dataType, nlohmann::json &serializedData);

    /**
     * @brief Serialize wether a status transmission failed
     * @param requestStatus wether the request was successful or not
     * @return json of the request as such
     * {
     * "action" : "status_transmission",
     * "domain" : "status_transmission",
     * "status" : "success | failure"
     * }
     */
    static nlohmann::json serializeStatusTransmission(RequestStatus requestStatus);
    /**
     * @brief serialize a request to get a specific chat
     * @param requester requester
     * @param receiver receiver
     * @return json of request as such
     * {
     * {"action", "object_request"},
     * {"domain", "resource_request"},
     * {"data_type", "chats"},
     * {"sender", "flm"},
     * {"receiver", "de_doc"},
     * }
     */
    static nlohmann::json serializeFriendChatRequest(const std::string &requester, const std::string &receiver);
    /**
     * @brief get request to game corresponding to gameID
     * @param gameID gameId
     * @return json of request as such
     * {
     * {"action", "object_request"},
     * {"domain", "resource_request"},
     * {"data_type", "game_ids"},
     * {"game_id", 123123}
     * }
     */
    static nlohmann::json serializeRequestGameID(int gameID);
};
