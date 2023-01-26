#define CATCH_CONFIG_MAIN // catch provides a main function
#include <catch2/catch.hpp>

#include <Singleton.hpp>

struct FileSystem {};

TEST_CASE("Singleton should return the same instance every time it's called", "[Singleton]") {
	SingletonNew& firstOnlyInstance { SingletonNew::get() };
	SingletonNew& secondOnlyInstance { SingletonNew::get() };

	REQUIRE(&firstOnlyInstance == &secondOnlyInstance);
}
