#define CATCH_CONFIG_MAIN
#include <Prototype.hpp>
#include <catch2/catch.hpp>

TEST_CASE("", "") {
    auto contact{getBasicWorkContact()};

    CHECK(contact.name.empty());
    CHECK(contact.address.street == "Baker");
    CHECK(contact.address.city == "London");

    contact.name = "Jane";
}
