#pragma once

enum class ChatInteraction {
    USER_SEND_MESSAGE,
    SERVER_RELAY_MESSAGE,
    JOIN,
    LEAVE,
};

inline const char *toJsonString(ChatInteraction a)
{
    switch (a) {
    case ChatInteraction::USER_SEND_MESSAGE:
        return "user_send_message";
    case ChatInteraction::SERVER_RELAY_MESSAGE:
        return "server_relay_message";
    case ChatInteraction::JOIN:
        return "user_join_chatbox";
    case ChatInteraction::LEAVE:
        return "user_leave_chatbox";
    }
}
