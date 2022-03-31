#pragma once

enum class RequestStatus { SUCCESS, FAILURE, CONNECTION_LOST };

inline const char *toJsonString(RequestStatus s)
{
    switch (s) {
    case RequestStatus::SUCCESS:
        return "request_success";
    case RequestStatus::FAILURE:
        return "request_failure";
    case RequestStatus::CONNECTION_LOST:
        return "request_timeout";
    }
    return "";
}
