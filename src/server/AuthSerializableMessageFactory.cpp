// Written by Francesco Nieri

#include "AuthSerializableMessageFactory.h"

using json = nlohmann::json;

json AuthSerializableMessageFactory::serializeUserRequest(ClientAuthAction action, std::string username, std::string password)
{
    
    json requestJson = {{"action", toJsonString(action)}, {"username", username}, {"password", password}};
    return requestJson;
}

json AuthSerializableMessageFactory::serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn)
{
    json answerJson = {{"action", toJsonString(action)}, {"status", toJsonString(status)}, {"error", toJsonString(authReturn)}};
    return answerJson;
}

