#define CATCH_CONFIG_MAIN // catch provides a main function
#include <CodeBuilder.hpp>
#include <catch2/catch.hpp>

TEST_CASE(
    "CxxCodeBuilder constructs a valid class (Person) with two attributes",
    "[Builder]") {
    // expectation
    std::string expectedClassCode{"class Person {\n"
                                  "int number;\n"
                                  "int places;\n"
                                  "};\n"};

    // actual
    auto classCode{CxxCodeBuilder("class", "Person")
                       .addAttribute("int", "number")
                       .addAttribute("int", "places")
                       .build()};

    REQUIRE(expectedClassCode == classCode);
}
