
/**
 * @file ObjectExchangesSerializableMessageFactory.h
 * @brief MessageFactory for requests and answers exchanges between user and server
 * @author Francesco Nieri
 * @date 21/02/2022
 */

#pragma once

#include "MessageEnums/Actions/ObjectExchanges.h"
#include "MessageEnums/Status.h"
#include <nlohmann/json.hpp>

class ObjectExchangesSerializableMessageFactory
{
public:
    /**
     * @brief serialize a user request of data
     * @param requestExchange must be -> OBJECT_REQUEST
     * @param dataType Type of data the user wants to requesto
     * @throw Assertion error if requestExchange != Exchange::OBJECT_REQUEST
     * @return json of the request as such
     * {
     * "action" : "object_request",
     * "data_type" : "leaderboard | friend_list ...",
     * }
     */
    nlohmann::json serializeRequestExchange(Exchange requestExchange, DataType dataType) const;
    /**
     * @brief serialize an answer from server to user
     * @param answerExchange must be -> OBJECT_ANSWER
     * @param dataType type of data the user has asked
     * @throw Assertion error if requestExchange != Exchange::OBJECT_ANSWER
     * @return json of the request as such
     * {
     * "action" : "object_answer",
     * "data_type" : "leaderboard | friend_list",
     * "serialized_data" : "json_serialized_object"
     * } 
     */
    nlohmann::json serializeAnswerExchange(Exchange answerExchange, DataType dataType, Serializable serializableData) const;

    /**
     * @brief Serialize wether a status transmission failed
     * @param transmission must be -> STATUS_TRANSMISSION
     * @param requestStatus wether the request was successful or not

     * @throw Assertion error if transmission != Ezchange::STATUS_TRANSMISSION
     * @return json of the request as such
     * {
     * "action" : "status_transmission",
     * "status" : "success | failure"
     * }
     */
    nlohmann::json serializeStatusTransmission(Exchange transmission, RequestStatus requestStatus) const;
}
