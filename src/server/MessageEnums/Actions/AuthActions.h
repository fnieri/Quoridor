/**
 * @file AuthActions.h
 * @author Francesco Nieri
 * @brief Enumerations representing auth actions used in json communication
 * @date 2022-02-22
 * 
 * 
 */

#pragma once

/// Enum representing auth actions that can be done by an user
enum class ClientAuthAction { 
    LOGIN, ///< Login 
    REGISTRATION ///< Registration
};

/**
 * @brief Output ClientAuthAction to a string used in json communication
 * 
 * @param a ClientAuthAction
 * @return const char* Json output
 */
inline const char *toJsonString(ClientAuthAction a)
{
    switch (a) {
    case ClientAuthAction::LOGIN:
        return "login";
    case ClientAuthAction::REGISTRATION:
        return "registration";
    }
}
// https://stackoverflow.com/questions/5093460/how-to-convert-an-enum-type-variable-to-a-string

/**
 * @brief Output ClientAuthAction to a string used in UI output to client
 * 
 * @param a ClientAuthAction
 * @return const char* string output
 */
inline const char *toOutputString(ClientAuthAction a)
{
    switch (a) {
    case ClientAuthAction::LOGIN:
        return "Log in to Quoridor";
    case ClientAuthAction::REGISTRATION:
        return "Create an account";
    }
}

/// Enum representing the response that the server gives to the client when registering
enum class ServerAuthReturn {
    CORRECT, ///< When auth is correct
    LOGIN_INCORRECT_USERNAME, ///< User input wrong username
    LOGIN_INCORRECT_PASSWORD, ///< User input wrong password
    REGISTER_PASSWORD_TOO_SHORT, ///< User registered with a password that was too short
    REGISTER_PASSWORD_TOO_LONG, ///< User registered with a password that was too long
    REGISTER_USERNAME_IN_USE, ///< The username already appears in the database
    REGISTER_WRONG_CHARACTERS ///< The username input characters that do not fit UTF-8 encoding
};

/**
 * @brief Output ServerAuthReturn to a string used in json communication
 * 
 * @param a ServerAuthReturn
 * @return const char* Json output
 */
inline const char *toJsonString(ServerAuthReturn a)
{
    switch (a) {
    case ServerAuthReturn::CORRECT:
        return "auth_correct";
    case ServerAuthReturn::LOGIN_INCORRECT_USERNAME:
        return "login_wrong_username";
    case ServerAuthReturn::LOGIN_INCORRECT_PASSWORD:
        return "login_wrong_password";
    case ServerAuthReturn::REGISTER_PASSWORD_TOO_SHORT:
        return "register_psw_too_short";
    case ServerAuthReturn::REGISTER_PASSWORD_TOO_LONG:
        return "register_psw_too_long";
    case ServerAuthReturn::REGISTER_USERNAME_IN_USE:
        return "register_username_in_use";
    case ServerAuthReturn::REGISTER_WRONG_CHARACTERS:
        return "register_wrong_char";
    }
}


/**
 * @brief Output ServerAuthReturn to a string used in UI output to client
 * 
 * @param a ServerAuthReturn
 * @return const char* string output
 */
inline const char *toOutputString(ServerAuthReturn s)
{
    switch (s) {
    case ServerAuthReturn::CORRECT:
        return "Successful authentification";
    case ServerAuthReturn::LOGIN_INCORRECT_USERNAME:
        return "Username doesn't exits";
    case ServerAuthReturn::LOGIN_INCORRECT_PASSWORD:
        return "Password doesn't match username";
    case ServerAuthReturn::REGISTER_PASSWORD_TOO_SHORT:
        return "Password is too short, it must be x characters long...";
    case ServerAuthReturn::REGISTER_PASSWORD_TOO_LONG:
        return "Password is too long, it must be x characters long...";
    case ServerAuthReturn::REGISTER_USERNAME_IN_USE:
        return "Username is already in use";
    case ServerAuthReturn::REGISTER_WRONG_CHARACTERS:
        return "You must only use letters, numbers, or special characters @#()[]{}!\"£$%&/()=?^";
    }
}