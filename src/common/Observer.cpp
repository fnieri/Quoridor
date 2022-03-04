/**
 * @file Observer.cpp
 * @author Boris Petrov
 * @brief Implementation of the observer pattern
 * @date 02/25/22
 */

#include "Observer.h"

#include "QuoridorEvent.h"

#include <algorithm>
#include <vector>

void Subject::registerObserver(Observer *observer)
{
    m_observers.push_back(observer);
}

void Subject::removeObserver(Observer *observer)
{
    // This is quite verbose but the only way
    // as of C++14. There is a better solution
    // in C++20 but, well, it's not available
    // at the NO...
    //
    // std::erase(m_observers, observer); // C++20
    m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Subject::notifyObservers(QuoridorEvent event) const
{
    for (auto &observer : m_observers)
        observer->update(event);
}
