/**
 * @file Point.cpp
 * @author Boris Petrov
 * @brief A position in a 2 dimentional grid
 * @date 02/25/22
 */

#include "src/common/Point.h"

#include <nlohmann/json.hpp>

#include <stdexcept>

using json = nlohmann::json;

// Point

Point::operator std::string() const noexcept
{
    return "(" + std::to_string(x()) + ", " + std::to_string(y()) + ")";
}

Point Point::operator+(const Point &rhs) const noexcept
{
    return {x() + rhs.x(), y() + rhs.y()};
}

Point Point::operator-(const Point &rhs) const noexcept
{
    return {x() - rhs.x(), y() - rhs.y()};
}

Point Point::operator*(const int &mult) const noexcept
{
    return {mult * x(), mult * y()};
}

Point Point::operator/(const int &div) const
{
    if (div == 0)
        throw std::runtime_error("Division by 0!");

    return {x() / div, y() / div};
}

bool Point::operator==(const Point &rhs) const noexcept
{
    return x() == rhs.x() && y() == rhs.y();
}

bool Point::operator!=(const Point &rhs) const noexcept
{
    return x() != rhs.x() || y() != rhs.y();
}

json Point::serialized()
{
    json pointJson = {{"x", x()}, {"y", y()}};
    return pointJson;
}

Point Point::deserialized(const std::string &ser)
{
    auto deser(json::parse(ser));
    return Point {deser["x"], deser["y"]};
}
