/**
 * @file BoardComponent.h
 * @author Nargis, Lèo, Anne-Marie
 * @brief Class representing a baord Component
 * @date 2022-03-04
 *
 */

#pragma once

/**
 * A container class for the contents of the Board.
 * Is only used as a superclass for Cell and Corridor.
 */
class BoardComponent
{
protected:
    /// Defines the state of that Board component.
    bool occupied = false;

public:
    /**
     * Returns the occupied state.
     *
     * @returns bool
     */
    bool isOccupied();

    // Add at least one virtual function to make the type polymorphic
    virtual ~BoardComponent() = default;
};