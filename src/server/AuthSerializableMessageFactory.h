/**
 * @file AuthSerializableMessageFactory.h
 * @author Francesco
 * @brief Message Factory for authentification messages between client and server
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "MessageEnums/Actions/AuthActions.h"
#include "MessageEnums/Status.h"
#include "SerializableMessageFactory.h"

#include <nlohmann/json.hpp>

#include <string>

class AuthSerializableMessageFactory : public SerializableMessageFactory
{
public:
    nlohmann::json serializeUserRequest(ClientAuthAction action, std::string username, std::string password);
    nlohmann::json serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn);
};