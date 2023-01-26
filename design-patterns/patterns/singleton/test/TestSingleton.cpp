#define CATCH_CONFIG_MAIN // catch provides a main function
#include <catch2/catch.hpp>

#include <Singleton_old.hpp>

template <typename T, typename... Args>
bool all_equal(T&& first, T&& second, Args&&... args) {
	return (first == second) and all_equal(second, std::forward<Args>(args)...);
}

template <typename T>
bool all_equal(T&& first, T&& second) {
	return (first == second);
}

// TEST_CASE("Singleton should return an object that's not null", "[Singleton]") {
// 	Singleton& onlyInstance { Singleton::get() };
//
// 	REQUIRE(&onlyInstance != nullptr);
// }

TEST_CASE("Singleton should return the same instance every time it's called", "[Singleton]") {
	Singleton& firstOnlyInstance { Singleton::get() };
	Singleton& secondOnlyInstance { Singleton::get() };
	Singleton& thirdOnlyInstance { Singleton::get() };
	// Same addresses
	REQUIRE(all_equal(&firstOnlyInstance, &secondOnlyInstance));
}

