#define CATCH_CONFIG_MAIN // catch provides a main function
#include <Builder.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Builder should construct a valid object", "[Builder]") {
    HtmlElement elem{HtmlElement::create("p")
                         .addChild("p", "Hello, World!")
                         .addChild("li", "list 1")
                         .build()};
    std::cout << elem.str();
}
