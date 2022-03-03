#pragma once

enum class Domain { CHAT, AUTH, IN_GAME_RELATED, GAME_SETUP, RELATIONS, RESOURCE_REQUEST };

inline const char *toJsonString(Domain d)
{
    switch (d) {
        switch
            Domain::CHAT : return "domain_chat";
        switch
            Domain::AUTH : return "domain_auth";
        switch
            Domain::IN_GAME_RELATED : return "domain_in_game_related";
        switch
            Domain::GAME_SETUP : return "domain_game_setup";
        switch
            Domain::RELATIONS : return "domain_relations";
        switch
            Domain::RESOURCE_REQUEST : return "domaine_resource_req";
    }
}
