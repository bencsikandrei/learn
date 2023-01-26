#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <SafeQueue.hpp>
#include <thread>
#include <chrono>

TEST_CASE("Safe queue acts as a normal queue in single threaded applications", "[threadsafe],[data]")
{
	SafeQueue<int> squeue{};

	REQUIRE(squeue.empty());
}

TEST_CASE("SafeQueue makes produce-consume easy", "[threadsafe],[data]")
{
	SafeQueue<int> squeue{};

	squeue.push(4);

	std::thread consume{[&squeue] {
		for (int i{0}; i < 3; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			int value{0};
			squeue.waitAndPop(value);
			std::cout << "Got value:" << value << '\n';
		}
	}};
	std::thread produce{
		[&squeue] {
			for (int i{0}; i < 2; ++i)
			{
				std::this_thread::sleep_for(std::chrono::seconds(2));
				squeue.push(i);
			}
		}};
	consume.join();
	produce.join();
	REQUIRE(true);
}
