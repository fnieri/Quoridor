/**
 * @file Stringable.h
 * @author Boris Petrov
 * @brief What every printable object should inherit
 * @date 02/25/22
 */

#pragma once

#include <iosfwd>
#include <string>

struct Stringable {
    explicit virtual operator std::string() const noexcept = 0;
};

std::ostream &operator<<(std::ostream &, const Stringable &);
