#pragma once 
#include <thread>
#include <chrono>
#include <utility>

struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;
    virtual ~NonCopyable() = default;
};

template <typename Func, typename ... Args>
std::thread make_thread(Func&& f, Args&& ... args) {
    return std::thread(std::forward<Func>(f), std::forward<Args>(args)...);
}

using TimePoint = std::chrono::high_resolution_clock::time_point;


template<typename F, typename... Args>
double bench(F func, Args&&... args)
{
    TimePoint start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    TimePoint end =  std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}