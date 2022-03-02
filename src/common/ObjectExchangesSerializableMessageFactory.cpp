#include "ObjectExchangesSerializableMessageFactory.h"

#include "MessageEnums/Domain.h"
using json = nlohmann::json;

json ObjectExchangesSerializableMessageFactory::serializeRequestExchange(DataType dataType)
{
    json requestJson
        = {{"action", toJsonString(Exchange::OBJECT_REQUEST)}, {"domain", toJsonString(Domain::RESOURCE_REQUEST)}, {"data_type", toJsonString(dataType)}};
    return requestJson;
}

json ObjectExchangesSerializableMessageFactory::serializeAnswerExchange(DataType dataType, json &serializedData)
{
    json answerJson = {{"action", toJsonString(Exchange::OBJECT_ANSWER)}, {"data_type", toJsonString(dataType)},
        {"domain", toJsonString(Domain::RESOURCE_REQUEST)}, {"serialized_data", serializedData}};
    return answerJson;
}

json ObjectExchangesSerializableMessageFactory::serializeStatusTransmission(RequestStatus requestStatus)
{
    json transmissionJson = {
        {"action", toJsonString(Exchange::STATUS_TRANSMISSION)}, {"domain", toJsonString(Domain::RESOURCE_REQUEST)}, {"status", toJsonString(requestStatus)}};
    return transmissionJson;
}

json ObjectExchangesSerializableMessageFactory::serializeFriendChatRequest(const std::string &requester, const std::string &receiver)
{
    json chatJson = {{"action", toJsonString(Exchange::OBJECT_REQUEST)}, {"domain", toJsonString(Domain::RESOURCE_REQUEST)},
        {"data_type", toJsonString(DataType::CHATS)}, {"sender", requester}, {"receiver", receiver}};
    return chatJson;
}

json ObjectExchangesSerializableMessageFactory::serializeRequestGameID(int gameID)
{
    json gameJson = {{"action", toJsonString(Exchange::OBJECT_REQUEST)}, {"domain", toJsonString((Domain::RESOURCE_REQUEST))},
        {"data_type", toJsonString(DataType::GAME_IDS)}, {"game_id", gameID}};
    return gameJson;
}