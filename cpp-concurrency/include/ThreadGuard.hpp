#pragma once

#include <Utils.hpp>
#include <thread>

class ThreadGuard final : private NonCopyable {
public:
    explicit ThreadGuard(std::thread& ugT) : t{ugT} {}
    ~ThreadGuard() {
        if(t.joinable())
            t.join();
    }
private:
    std::thread& t;
};

