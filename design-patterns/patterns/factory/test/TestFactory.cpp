#define CATCH_CONFIG_MAIN // catch provides a main function
#include <catch2/catch.hpp>

#include <Factory.hpp>

TEST_CASE("PointFactory returns a valid point from cartesian", "PointFactory") {
    Point p1{PointFactory::fromCartesian(1, 2)};

    CHECK(p1.X == 1);
    CHECK(p1.Y == 2);
}

TEST_CASE("PointerFactory returns a valid Point from Polar", "PointFactory") {}
