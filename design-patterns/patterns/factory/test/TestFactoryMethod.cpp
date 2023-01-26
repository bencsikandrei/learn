#define CATCH_CONFIG_MAIN // catch provides a main function
#include <catch2/catch.hpp>

#include <FactoryMethod.hpp>

TEST_CASE("PointFactory returns a valid Point from Cartesian", "PointFactory") {
    auto pointCartesian{Point::newCartesian(10, 20)};

    REQUIRE(pointCartesian.X == 10);
    REQUIRE(pointCartesian.Y == 20);
}

TEST_CASE("PointerFactory returns a valid Point from Polar", "PointFactory") {
    auto pointCartesian{Point::newPolar(5, 51.13010235)};

    REQUIRE(pointCartesian.X == Approx(3.2446400f));
    REQUIRE(pointCartesian.Y == Approx(3.80425001));
}
