#pragma once

#include <nlohmann/json_fwd.hpp>

class Serializable
{
public:
    virtual nlohmann::json serialized() = 0;
    virtual ~Serializable()=default;
};
