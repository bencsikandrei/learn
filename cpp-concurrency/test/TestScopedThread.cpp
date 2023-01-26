#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <ScopedThread.hpp>

TEST_CASE("Scoped thread calls join on it's thread when scope ends (no terminate() called)", "[scoped]") {
	ScopedThread st { std::thread([]()
		{
			std::cout << "Do this and don't call terminate when this scope ends because the scoped thread calls join :)\n";
		}
	)};

	REQUIRE(true);
}
