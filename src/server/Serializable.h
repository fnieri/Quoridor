#pragma once

#include <nlohmann/json.hpp>

class Serializable
{
    nlohmann::json serialized();
};
