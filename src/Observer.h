/**
 * Classes implementing the Observer design pattern.
 */

#pragma once

#include "Event.h"

#include <algorithm>
#include <vector>

class Observer
{
public:
    virtual void update(Event) = 0;

    virtual ~Observer() noexcept = default;
};

class Subject
{
public:
    virtual void registerObserver(Observer *);
    virtual void removeObserver(Observer *);
    virtual void notifyObservers(Event = Event::Modified) const;

    virtual ~Subject() noexcept = default;

protected:
    std::vector<Observer *> m_observers {};
};
