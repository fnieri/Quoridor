/**
 * @file AuthHandler.cpp
 * @author Boris Petrov
 * @brief Register and log clients in
 * @date 02/25/22
 */

#include "AuthHandler.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * AuthHandler
 */

std::string AuthHandler::tryRegister(const std::string &serRequest)
{
    json requestAnswer;
    auto request {json::parse(serRequest)};

    if (DatabaseHandler::createAccount(request["username"], request["password"])) {
        requestAnswer = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::REGISTER, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT);
    } else {
        requestAnswer
            = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::REGISTER, RequestStatus::FAILURE, ServerAuthReturn::USERNAME_IN_USE);
    }

    return requestAnswer.dump();
}

std::string AuthHandler::tryLogIn(const std::string &serMessage)
{
    json requestAnswer;
    auto request {json::parse(serRequest)}; //

    if (DatabaseHandler::checkLogin(request["username"], request["password"])) {
        requestAnswer = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::LOGIN, RequestStatus::SUCCESS, ServerAuthReturn::CORRECT);
    } else {
        // TODO: see for two types of login failures
        requestAnswer
            = SerializableMessageFactory::serializeServerAnswer(ClientAuthAction::LOGIN, RequestStatus::FAILURE, ServerAuthReturn::LOGIN_INCORRECT_USERNAME);
    }

    return requestAnswer.dump();
}

std::string AuthHandler::processRequest(const std::string &serRequest)
{
    std::string requestAnswer;
    auto request {json::parse(serRequest)};

    if (request["action"] == toJsonString(ClientAuthAction::REGISTRATION)) {
        requestAnswer = tryRegister(serRequest);
    } else if (request["action"] == toJsonString(ClientAuthAction::LOGIN)) {
        requestAnswer = tryLogIn(serRequest);
    }

    return requestAnswer;
}
