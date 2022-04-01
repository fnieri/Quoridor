#pragma once

#include "src/common/Point.h"
#include <nlohmann/json.hpp>

class Action
{
public:
    Action();
    virtual ~Action();
    virtual bool isWallAction() = 0;
    virtual bool isPlayerAction() = 0;
    virtual bool executeAction() = 0;
    virtual nlohmann::json serialized() = 0;
    virtual Point getDestination() const = 0;
};