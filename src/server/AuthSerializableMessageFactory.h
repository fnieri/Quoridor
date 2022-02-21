/**
 * @file AuthSerializableMessageFactory.h
 * @author Francesco
 * @brief Message Factory for authentification messages between client and server
 * @version 0.1
 * @date 2022-02-17
 *
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
    /**
     * @brief serialize user Json Request when trying to authentify
     *
     * @param action Login or register
     * @param username Username of the user
     * @param password Non encrypted password of the user
     * @return nlohmann::json Json of request as such
     *
     */
    nlohmann::json serializeUserRequest(ClientAuthAction action, std::string username, std::string password);
    /**
     * @brief serialize server json response
     *
     * @param action Login or register
     * @param status Successful or failed auth
     * @param authReturn Return which auth error occured
     * @return nlohmann::json
     */
    nlohmann::json serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn);
};
