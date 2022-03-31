/**
 * @file AuthSerializableMessageFactory.h
 * @author Francesco
 * @brief Message Factory for authentification messages between client and server
 * @date 2022-02-17
 *
 *
 */

#pragma once

#include "MessageEnums/Actions/AuthActions.h"
#include "MessageEnums/Status.h"

#include <nlohmann/json_fwd.hpp>

#include <string>

class AuthSerializableMessageFactory
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
    static nlohmann::json serializeUserRequest(ClientAuthAction action, const std::string &username, const std::string &password);
    /**
     * @brief serialize server json response
     *
     * @param action Login or register
     * @param status Successful or failed auth
     * @param authReturn Return which auth error occured
     * @return nlohmann::json
     */
    static nlohmann::json serializeServerAnswer(ClientAuthAction action, RequestStatus status, ServerAuthReturn authReturn, const std::string& username);
};
