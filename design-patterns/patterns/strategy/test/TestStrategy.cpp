#define CATCH_CONFIG_MAIN

#include <Strategy.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Add behavior to object", "Strategy") {
    auto qb{std::make_unique<QuackLoud>()};
    Duck d1{};
    d1.quack();
    d1.setQuackBehavior(std::move(qb));
    d1.setFlightBehavior(std::make_unique<FlyHigh>());
    d1.quack();
    d1.fly();
}
