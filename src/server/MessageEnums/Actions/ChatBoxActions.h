enum class ClientChatInteraction { SEND_MESSAGE, JOIN, LEAVE };

inline const char *toJsonString(ClientChatInteraction a)
{
    switch (a) {
    case ClientChatInteraction::SEND_MESSAGE:
        return "user_send_message";
    case ClientChatInteraction::JOIN:
        return "user_join_chatbox";
    case ClientChatInteraction::LEAVE:
        return "user_leave_chatbox";
    }
}
