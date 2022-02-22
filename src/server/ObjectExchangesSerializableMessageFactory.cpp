#include "ObjectExchangesSerializableMessageFactory.h"

using json = nlohmann::json;

json ObjectexchangesSerializableMessageFactory::serializeRequestExchange(Serializable dataType) const
{
    json requestJson = {{"action", toJsonString(Exchange::OBJECT_REQUEST)}, {"data_type", dataType.asDataType()}};
    return requestJson;
}

json ObjectExchangesSerializableMessageFactory::serializeAnswerExchange(DataType dataType, Serializable serializableData) const
{
    json answerJson
        = {{"action", toJsonString(Exchange::OBJECT_ANSWER)}, {"data_type", toJsonString(dataType)}, {"serialized_data", serializableData.serialized()}};
    return answerJson;
}

json ObjectExchangesSerializableMessageFactory::serializeStatusTransmission(RequestStatus requestStatus) const
{
    json transmissionJson = {{"action", toJsonString(Exchange::STATUS_TRANSMISSION)}, {"status", toJsonString(requestStatus)}};
    return transmissionJson;
}
