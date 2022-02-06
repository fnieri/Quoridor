#include "Stringable.h"

#include <iostream>

std::ostream &operator<<(std::ostream &os, const Stringable &s)
{
    os << static_cast<std::string>(s);
    return os;
}
