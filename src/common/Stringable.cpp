/**
 * @file Stringable.cpp
 * @author Boris Petrov
 * @brief What every printable object should inherit
 * @date 02/25/22
 */

#include "Stringable.h"

#include <iostream>

std::ostream &operator<<(std::ostream &os, const Stringable &s)
{
    os << static_cast<std::string>(s);
    return os;
}
