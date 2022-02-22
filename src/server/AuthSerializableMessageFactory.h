#pragma once

#include "MessageEnums/Actions/AuthActions.h"
#include "MessageEnums/Status.h"
#include "SerializableMessageFactory.h"

#include <string>

class AuthSerializableMessageFactory : public SerializableMessageFactory
{
public:
    Json::Value serializeUserRequest(ClientAuthAction action, std::string username, std::string password);
    Json::Value serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn);
    Json::Value serialize();
};