#pragma once

#include <nlohmann/json.hpp>

class Serializable
{
public:
    virtual nlohmann::json serialized() {};
    virtual ~Serializable()=default;

};
