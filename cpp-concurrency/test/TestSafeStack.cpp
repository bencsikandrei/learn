#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <SafeStack.hpp>

TEST_CASE("SafeStack is empty at construction", "[threadsafe],[data]") {
	SafeStack<int> sstack{};

	REQUIRE(sstack.empty());
}


TEST_CASE("SafeStack is not empty after push", "[threadsafe],[data]") {
	SafeStack<int> sstack{};
	sstack.push(1);

	REQUIRE(not sstack.empty());
}
