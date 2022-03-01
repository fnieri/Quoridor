#pragma once

#include <nlohmann/json.hpp>

class Serializable
{
public:
    virtual nlohmann::json serialized()=0;
    virtual ~Serializable()=default;
};
