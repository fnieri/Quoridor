/**
 * @file QuoridorEvent.h
 * @author Boris Petrov
 * @brief Events occuring
 * @date 02/25/22
 */

#pragma once

enum class QuoridorEvent {
    Modified, ///< Generic modification
    EloModified,
    LeaderboardModified,
    RelationsModified,
    ChatsUpdated,
    FriendsUpdated,
    GameIdsUpdated,
};
