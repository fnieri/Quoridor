#include "ObjectExchangesSerializableMessageFactory.h"

using json = nlohmann::json;

json ObjectexchangesSerializableMessageFactory::serializeRequestExchange(Serializable dataType)
{
    json requestJson = {{"action", toJsonString(Exchange::OBJECT_REQUEST)}, {"domain", toJsonString(Domain::RESOURCE_REQUEST)}, {"data_type", dataType.asDataType()}};
    return requestJson;
}

json ObjectExchangesSerializableMessageFactory::serializeAnswerExchange(DataType dataType, Serializable serializableData)
{
    json answerJson
        = {{"action", toJsonString(Exchange::OBJECT_ANSWER)}, {"data_type", toJsonString(dataType)}, {"domain", toJsonString(Domain::RESOURCE_REQUEST)}, {"serialized_data", serializableData.serialized()}};
    return answerJson;
}

json ObjectExchangesSerializableMessageFactory::serializeStatusTransmission(RequestStatus requestStatus)
{
    json transmissionJson = {{"action", toJsonString(Exchange::STATUS_TRANSMISSION)}, {"domain", toJsonString(Domain::RESOURCE_REQUEST)},  {"status", toJsonString(requestStatus)}};
    return transmissionJson;
}
