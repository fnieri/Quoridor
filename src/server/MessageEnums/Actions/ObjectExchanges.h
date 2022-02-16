enum class Answer {
    OBJECT_ANSWER,
};

inline const char *toJsonString(Answer a)
{
    switch (a) {
    case Answer::OBJECT_ANSWER:
        return "object_answer";
    }
}

enum class Request {
    OBJECT_REQUEST,
};

inline const char *toJsonString(Request r)
{
    switch (r) {
    case Request::OBJECT_REQUEST:
        return "object_request";
    }
}

enum class StatusTransmission {
    STATUS_TRANSMISSION,
};

inline const char *toJsonString(StatusTransmission s)
{
    switch (s) {
    case StatusTransmission::STATUS_TRANSMISSION:
        return "status_transmission";
    }
}