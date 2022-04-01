#pragma once

enum class ClientProperty {
    SERVER_IP,
    PORT
};

inline const char* toConfigString(ClientProperty c)
{
    switch (c) {
        case ClientProperty::SERVER_IP:
            return "server_ip";
        case ClientProperty::PORT:
            return "server_port";
    }
    return "";
}

enum class ServerProperty {
    DB_ADDRESS,
    PORT
};

inline const char* toConfigString(ServerProperty s)
{
    switch(s) {
        case ServerProperty::DB_ADDRESS:
            return "db_address";
        case ServerProperty::PORT:
            return "server_port";
    }
    return "";
}
