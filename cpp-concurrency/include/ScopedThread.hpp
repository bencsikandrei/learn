#pragma once 
#include <thread>

#include <Utils.hpp>

class ScopedThread final : private NonCopyable {
public:
    explicit ScopedThread(std::thread t) : mT { std::move(t) } {
        // check if mT is joinable ..
    }
    ~ScopedThread() { mT.join(); }
private:
    std::thread mT;
};