/**
 * @file AuthHandler.cpp
 * @author Boris Petrov
 * @brief Register and log clients in
 * @date 02/25/22
 */

#include "AuthHandler.h"

#include "src/common/SerializableMessageFactory.h"
#include "src/server/Database.h"
#include "src/server/UserHandler.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * AuthHandler
 */

AuthHandler::AuthHandler(UserHub &userHub)
    : m_userHub {userHub}
{
}

std::string AuthHandler::tryRegister(const std::string &serRequest)
{
    json requestAnswer;
    auto request(json::parse(serRequest));

    if (DatabaseHandler::createAccount(request["username"], request["password"])) {
        requestAnswer = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::REGISTRATION, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT, request["username"]);

    } else {
        requestAnswer = SerializableMessageFactory::serializeServerAnswer(
            ClientAuthAction::REGISTRATION, RequestStatus::FAILURE, ServerAuthReturn::REGISTER_USERNAME_IN_USE, request["username"]);
    }

    return requestAnswer.dump();
}

std::string AuthHandler::tryLogIn(const std::string &serRequest)
{
    json requestAnswer;
    auto request(json::parse(serRequest));

    if (!m_userHub.isConnected(request["username"]) && DatabaseHandler::checkLogin(request["username"], request["password"])) {
        requestAnswer = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::LOGIN, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT, request["username"]);

    } else {
        // TODO: see for two types of login failures
        requestAnswer
            = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::LOGIN, RequestStatus::FAILURE, ServerAuthReturn::LOGIN_INCORRECT_USERNAME, request["username"]);
    }

    return requestAnswer.dump();
}

std::string AuthHandler::processRequest(const std::string &serRequest)
{
    std::string requestAnswer;
    auto request(json::parse(serRequest));

    if (request["action"] == toJsonString(ClientAuthAction::REGISTRATION)) {
        requestAnswer = tryRegister(serRequest);

    } else if (request["action"] == toJsonString(ClientAuthAction::LOGIN)) {
        requestAnswer = tryLogIn(serRequest);
    }

    return requestAnswer;
}
