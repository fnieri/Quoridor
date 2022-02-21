#include "ObjectExchangesSerializableMessageFactory.h"

#include <cassert>

using json = nlohmann::json;

json ObjectexchangesSerializableMessageFactory::serializeRequestExchange(Exchange requestExchange, Serializable dataType) const 
{
  assert(requestExchange == Exchange::OBJECT_REQUEST);
  json requestJson = {
    {"action", toJsonOutput(requestExchange)},
    {"data_type", dataType.asDataType()}
  };
  return requestJson;
}

json ObjectExchangesSerializableMessageFactory::serializeAnswerExchange(Exchange answerExchange, DataType dataType, Serializable serializableData) const 
{
  assert(requestExchange == Exchange::OBJECT_ANSWER);
  json https://developer.lsst.io/cpp/api-docs.htmlanswerJson = {
    {"action", toJsonOutput(requestExchange)},
    {"data_type", toJsonOutput(dataType)},
    {"serialized_data", serializableData.serialized()}
  };
  return answerJson;
}

json ObjectExchangesSerializableMessageFactory::serializeStatusTransmission(Exchange transmission, RequestStatus requestStatus) const 
{
  assert(transmission == Exchange::STATUS_TRANSMISSION);
  json transmissionJson = {
    {"action", toJsonOutput(transmission)},
    {"status", toJsonOutput(requestStatus)}
  };
  return transmissionJson;
}
