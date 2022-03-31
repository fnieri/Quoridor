#pragma once

enum class Domain { CHAT, AUTH, IN_GAME_RELATED, GAME_SETUP, RELATIONS, RESOURCE_REQUEST };

inline const char *toJsonString(Domain d)
{
    switch (d) {
    case Domain::CHAT:
        return "domain_chat";
    case Domain::AUTH:
        return "domain_auth";
    case Domain::IN_GAME_RELATED:
        return "domain_in_game_related";
    case Domain::GAME_SETUP:
        return "domain_game_setup";
    case Domain::RELATIONS:
        return "domain_relations";
    case Domain::RESOURCE_REQUEST:
        return "domaine_resource_req";
    }
    return "";
}
