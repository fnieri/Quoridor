#pragma once

// Written by Francesco Nieri
enum class ClientAuthAction { LOGIN, REGISTRATION };

// https://stackoverflow.com/questions/5093460/how-to-convert-an-enum-type-variable-to-a-string
inline const char *toOutputString(ClientAuthAction a)
{
    switch (a) {
    case ClientAuthAction::LOGIN:
        return "Log in to Quoridor";
    case ClientAuthAction::REGISTRATION:
        return "Create an account";
    }
}

enum class ServerAuthReturn {
    CORRECT,
    LOGIN_INCORRECT_USERNAME,
    LOGIN_INCORRECT_PASSWORD,
    REGISTER_PASSWORD_TOO_SHORT,
    REGISTER_PASSWORD_TOO_LONG,
    REGISTER_USERNAME_IN_USE,
    REGISTER_WRONG_CHARACTERS
};

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

inline const char *toJsonString(ClientAuthAction a)
{
    switch (a) {
    case ClientAuthAction::LOGIN:
        return "login";
    case ClientAuthAction::REGISTRATION:
        return "registration";
    }
}

inline const char *toOutputSing(ServerAuthReturn s)
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