#pragma once

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue {
public:
    SafeQueue() = default;
    SafeQueue(SafeQueue const& rhs) {
        std::lock_guard<std::mutex> lg { mut };
        data = rhs.data;
    }
    void push(T newValue) {
        std::lock_guard<std::mutex> lg {mut};
        data.push(newValue);
        dataCondition.notify_one();
    }
    void waitAndPop(T& value) {
        std::unique_lock<std::mutex> ul{mut};
        dataCondition.wait(ul, [this]{ return not data.empty(); });
        value = data.front();
        data.pop();
    }

    std::shared_ptr<T> waitAndPop() {
        std::unique_lock<std::mutex> ul{mut};
        dataCondition.wait(ul, [this]{ return not data.empty(); });
        std::shared_ptr<T> res{ std::make_shared<T>(data.front()) };
        data.pop();
        return res;
    }
    
    bool tryPop(T& value) {
        std::lock_guard<std::mutex> lg{mut};
        if(data.empty()) {
            return false;
        }
        value = data.front();
        data.pop();
        return true;
    }

    std::shared_ptr<T> tryPop() {
        std::lock_guard<std::mutex> lg { mut };
        if(data.empty()) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> res { std::make_shared<T>(data.front() ) };
        data.pop();
        return res;
    }

    bool empty() {
        std::lock_guard<std::mutex> lg{mut};
        return data.empty();
    }

private:
    mutable std::mutex mut;
    std::queue<T> data;
    std::condition_variable dataCondition;

};