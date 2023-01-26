#define CATCH_CONFIG_MAIN // catch provides a main function
#include <catch2/catch.hpp>

#include <DrinkFactory.hpp>

template <typename T> struct TypeTest;

TEST_CASE("Abstract factory for drinks", "DrinkFactory") {
    DrinkFactory df{};
    auto c{df.make("coffee")};
    std::unique_ptr<HotDrink> t = df.make("tea");
    c->prepare(100);
}
