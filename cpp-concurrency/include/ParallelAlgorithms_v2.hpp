#pragma once
#include <numeric>
#include <thread>
#include <algorithm>

namespace par
{
namespace detail
{
template <typename Iterator, typename T>
struct AccumulateBlock
{
    void operator()(Iterator begin, Iterator end, T &result)
    {
        std::cout << std::this_thread::get_id() << '\n';
        result = std::accumulate(begin, end, result);
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
    constexpr unsigned long minPerBlock { 25 };
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

    std::vector<T> results(nbOfThreads);
    std::vector<std::thread> threads(nbOfThreads - 1); // the main thread also :)

    Iterator blockBegin{begin};
    for(unsigned long i{0}; i < (nbOfThreads - 1); ++i) {
        auto& thread { threads[i] };
        auto& result { results[i] };
        Iterator blockEnd{blockBegin};
        std::advance(blockEnd, blockSize);
        thread = std::thread(
            detail::AccumulateBlock<Iterator, T>(),
            blockBegin, blockEnd, std::ref(result));
        blockBegin = blockEnd;
    }
    detail::AccumulateBlock<Iterator, T>()(
        blockBegin, end, results[nbOfThreads -1]
    );

    // join the threads 
    std::for_each(
        threads.begin(), threads.end(), 
        std::mem_fn(&std::thread::join)
    );
    return std::accumulate(results.begin(), results.end(), initial);
}
} // namespace par