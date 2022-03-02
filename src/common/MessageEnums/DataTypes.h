/**
 * @author Francesco Nieri
 * @brief Enums for data type transmission
 * @date 21/02/2022
 */

#pragma once
/**
 * @brief Enum representing data types which can be requested by an user
 *
 */
enum class DataType { GAME_ACTION, LEADERBOARD, FRIENDS_LIST, GAME_CONFIG, FRIEND_REQUESTS_SENT, FRIEND_REQUESTS_RECEIVED, CHATS, GAME_IDS };

inline const char *toJsonString(DataType d)
{
    switch (d) {
    case DataType::GAME_ACTION:
        return "game_action";
    case DataType::LEADERBOARD:
        return "leaderboard";
    case DataType::FRIENDS_LIST:
        return "friends_list";
    case DataType::GAME_CONFIG:
        return "game_config";
    case DataType::FRIEND_REQUESTS_SENT:
        return "friend_requests_sent";
    case DataType::FRIEND_REQUESTS_RECEIVED:
        return "friend_requests_received";
    case DataType::GAME_IDS:
        return "game_ids";
    case DataType::CHATS:
        return "chats";
    }
    return "";
}
