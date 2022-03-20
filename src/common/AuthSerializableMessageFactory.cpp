/**
 * @file AuthSerializableMessageFactory.cpp
 * @author Francesco Nieri
 * @brief Message Factory for Authentification Serializable Requests
 * @date 20/02/2022
 */

#include "AuthSerializableMessageFactory.h"
#include "MessageEnums/Domain.h"

using json = nlohmann::json;

json AuthSerializableMessageFactory::serializeUserRequest(ClientAuthAction action, const std::string &username, const std::string &password)
{
    json requestJson = {{"action", toJsonString(action)}, {"domain", toJsonString(Domain::AUTH)}, {"username", username}, {"password", password}};
    return requestJson;
}

json AuthSerializableMessageFactory::serializeServerAnswer(
    ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn, const std::string &username)
{
    json answerJson = {{"action", toJsonString(action)}, {"domain", toJsonString(Domain::AUTH)}, {"status", toJsonString(status)},
        {"error", toJsonString(authReturn)}, {"username", username}};
    return answerJson;
}
