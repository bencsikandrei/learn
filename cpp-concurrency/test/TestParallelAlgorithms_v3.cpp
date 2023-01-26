#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <ParallelAlgorithms_v3.hpp>
#include <vector>
#include <numeric>
#include <Utils.hpp>

TEST_CASE("parallel_accumulate returns initial when empty range", "[algorithm]") {
	std::vector<int> values{}; // empty vector
	constexpr int initialValue{0};

	int parallelResult = par::parallel_accumulate(values.begin(), values.end(), initialValue);

	REQUIRE(parallelResult == initialValue);
}

TEST_CASE("parallel_accumulate returns the correct result when passed two values", "[algorithm]") {
	std::vector<int> values{2, 3}; // empty vector
	constexpr int initialValue{0};

	int parallelResult = par::parallel_accumulate(values.begin(), values.end(), initialValue);

	REQUIRE(parallelResult == 5);
}

TEST_CASE("parallel_accumulate returns the correct result when passed two values and an initial value != 0", "[algorithm]") {
	std::vector<int> values{2, 3}; // empty vector
	constexpr int initialValue{15};

	int parallelResult = par::parallel_accumulate(values.begin(), values.end(), initialValue);

	REQUIRE(parallelResult == (5 + initialValue));
}

TEST_CASE("parallel_accumulate returns the correct result when passed multiple values", "[algorithm]") {
	constexpr unsigned nbOfElems{10000};
	std::vector<unsigned> values(nbOfElems);
	std::iota(values.begin(), values.end(), 0u);
	unsigned long serialResult { std::accumulate(values.begin(), values.end(), 0u)};

	unsigned long parallelResult { 
		par::parallel_accumulate(values.begin(), values.end(), 0u)
	};

	REQUIRE(serialResult == parallelResult);
}	

TEST_CASE("parallel_accumulate is at least as fast as std::accumulate", "[algorithm]") {
	constexpr unsigned long long nbOfElems{1UL << 20};
	std::vector<unsigned> values(nbOfElems);
	std::iota(values.begin(), values.end(), 0u);

	auto serTime = bench(
		std::accumulate<std::vector<unsigned>::iterator, unsigned>, values.begin(), values.end(), 0u
	);

	auto parTime = bench(	
		par::parallel_accumulate<std::vector<unsigned>::iterator, unsigned>, values.begin(), values.end(), 0u
	);

	CHECK(serTime >= parTime);

}	


