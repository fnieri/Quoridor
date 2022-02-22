#pragma once

class BoardComponent
{
protected:
    bool occupied = false;

public:
    bool isOccupied();

    // Add at least one virtual function to make the type polymorphic
    virtual ~BoardComponent() = default;
};