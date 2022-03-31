#include <catch2/catch.hpp>

#include "src/common/Point.h"

#include <nlohmann/json.hpp>

#include <string>

SCENARIO("Basic operations")
{
    Point op1 {8, 10};
    Point op2 {-4, 0};

    GIVEN("Addition")
    {
        REQUIRE(op1 + op2 == Point {4, 10});
        REQUIRE(op2 + op1 == Point {4, 10});
    }

    GIVEN("Substraction")
    {
        REQUIRE(op1 - op2 == Point {12, 10});
        REQUIRE(op2 - op1 == Point {-12, -10});
    }

    GIVEN("Multiplication")
    {
        REQUIRE(op1 * 2 == Point {16, 20});
        REQUIRE(op1 * 1 == op1);
        REQUIRE(op1 * 0 == Point {0, 0});
    }

    GIVEN("Division")
    {
        REQUIRE(op1 / 2 == Point {4, 5});
        REQUIRE(op1 / 1 == op1);
        REQUIRE_THROWS(op1 / 0 == Point {0, 0});
    }
}

SCENARIO("String representation")
{
    REQUIRE(static_cast<std::string>(Point {8, 2}) == "(8, 2)");
}

SCENARIO("Serialization and deserialization")
{
    Point a {7, 9};

    REQUIRE(a.serialized() == nlohmann::json {{"x", 7}, {"y", 9}});
    REQUIRE(Point::deserialized(a.serialized().dump()) == a);
}
