/**
 * @file Observer.h
 * @author Boris Petrov
 * @brief Implementation of the observer pattern
 * @date 02/25/22
 */

#pragma once

#include "QuoridorEvent.h"

#include <algorithm>
#include <vector>

/**
 * The observer part of the pattern
 *
 * The Observer watches one or more Subjects whose
 * state is expected to change. When this occur,
 * the update method is called to allow the observer
 * to act accordingly.
 */
class Observer
{
public:
    /**
     * Method called to inform the observer of an event
     *
     * @param event event according to which the observer is to be updated
     */
    virtual void update(QuoridorEvent) = 0;

    virtual ~Observer() noexcept = default;
};

/**
 * The subject part of the pattern
 *
 * The Subject is watched by Observers. This means that
 * they have subscribed to be updated when events happen.
 * They can of course unsubsribe whenever they want.
 *
 * @note Usually, the events sent out are ones that change
 * the state of the Subject so that the Observer can update
 * itself. This can be very useful for the MVC design architecture
 * for example.
 */
class Subject
{
public:
    /**
     * Subscribe to event updates
     *
     * @param observer observer to subscribe
     */
    virtual void registerObserver(Observer *);
    /**
     * Unsubsribe from event updates
     *
     * @param observer observer to unsubscribe
     */
    virtual void removeObserver(Observer *);
    /**
     * Update Observers with a given Event
     *
     * @param event event to pass over
     */
    virtual void notifyObservers(QuoridorEvent = QuoridorEvent::Modified) const;

    virtual ~Subject() noexcept = default;

protected:
    std::vector<Observer *> m_observers {};
};
