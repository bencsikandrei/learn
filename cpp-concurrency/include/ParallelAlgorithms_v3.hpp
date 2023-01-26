#pragma once
#include <numeric>
#include <thread>
#include <algorithm>
#include <future>

namespace par
{
namespace detail
{
template <typename Iterator, typename T>
struct AccumulateBlock
{
    T operator()(Iterator begin, Iterator end)
    {
        // std::cout << std::this_thread::get_id() << '\n';
        return std::accumulate(begin, end, T{});
    }
};
} // namespace detail

template <typename Iterator, typename T>
T parallel_accumulate(Iterator begin, Iterator end, T initial)
{
    unsigned long const length = std::distance(begin, end);
    if (not length)
    {
        return initial;
    }
    constexpr unsigned long minPerThread { 25 };

    unsigned long const maxThreads { (length + minPerThread -1) / minPerThread };
    unsigned long const hwThreads { std::thread::hardware_concurrency() };
    unsigned long const nbOfThreads { 
        std::min(
            (hwThreads != 0) ? hwThreads : 2,
            maxThreads
        )
    };
    unsigned long const blockSize { length / nbOfThreads };

    std::vector<std::future<T>> results{};
    results.reserve(nbOfThreads - 1);

    Iterator blockBegin{begin};
    for(unsigned long i{0}; i < (nbOfThreads - 1); ++i) {
        Iterator blockEnd{blockBegin};
        std::advance(blockEnd, blockSize);
        results.emplace_back( std::async(std::launch::async, detail::AccumulateBlock<Iterator, T>(),
            blockBegin, blockEnd // saving futures in the vector
        ));
        blockBegin = blockEnd;
    }

    // Main thread should work as well !
    T mainRes = initial + detail::AccumulateBlock<Iterator, T>()(
        blockBegin, end
    );
    T finalResult {mainRes}; 
    for(auto& f: results) {
        finalResult += f.get(); 
    }
    return finalResult;
}
} // namespace par