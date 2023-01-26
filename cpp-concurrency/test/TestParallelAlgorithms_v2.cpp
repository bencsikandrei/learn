#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <ParallelAlgorithms_v2.hpp>
#include <vector>
#include <numeric>

TEST_CASE("Accumulate block returns it's result in a reference", "[algorithm]") {
	constexpr unsigned nbOfElems{10000};
	std::vector<unsigned> values(nbOfElems);
	std::iota(values.begin(), values.end(), 0u);
	unsigned long serialResult { std::accumulate(values.begin(), values.end(), 0u)};
	unsigned long blockResult {0u};

	par::detail::AccumulateBlock<std::vector<unsigned>::iterator, unsigned long>()(values.begin(), values.end(), blockResult);

	REQUIRE(blockResult == serialResult);
}

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