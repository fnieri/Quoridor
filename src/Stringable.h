#pragma once

// Forward declarations of io streams, see: https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/group__s27__2__iosfwd.html
#include <iosfwd>
#include <string>

struct Stringable {
    explicit virtual operator std::string() const noexcept = 0;
};

std::ostream &operator<<(std::ostream &, const Stringable &);

