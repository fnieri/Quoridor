// Written by Francesco Nieri

#include "AuthSerializableMessageFactory.h"

Json::Value AuthSerializableMessageFactory::serializeUserRequest(ClientAuthAction action, std::string username, std::string password)
{
    Json::Value requestJson;
    requestJson["action"] = toJsonString(action);
    requestJson["username"] = username;
    requestJson["password"] = password;
    return requestJson;
}

Json::Value AuthSerializableMessageFactory::serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn)
{
    Json::Value requestJson;
    requestJson["action"] = toJsonString(action); // Or to output, we should decide
    requestJson["status"] = toJsonString(status);
    requestJson["error"] = toJsonString(authReturn);
    return requestJson;
}