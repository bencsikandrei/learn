#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <ThreadGuard.hpp>

TEST_CASE("ThreadGuard takes a reference to an existing thread and calls join on it on scope end", "[guard]") {
	std::thread t1 { [](){ std::cout << "Thread guard will save me from terminate !\n"; } };
	ThreadGuard tg { t1 };
	REQUIRE(true);
}
