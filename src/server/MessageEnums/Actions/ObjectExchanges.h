/**
 * @author Francesco Nieri
 * @brief Enums for object exchanges
 * #date 21/02/2022
 *
*/

#pragma once
enum class Exchange{
    OBJECT_ANSWER,
    OBJECT_REQUEST,
    STATUS_TRANSMISSION
};

inline const char *toJsonString(Exchange e) {
    switch (e) {
    case Exchange::OBJECT_ANSWER:
        return "object_answer";
    case Exchange::OBJECT_REQUEST:
        return "object_request";
    case Exchange::STATUS_TRANSMISSION:
        return "status_transmission";    
    }
  return "";
}
