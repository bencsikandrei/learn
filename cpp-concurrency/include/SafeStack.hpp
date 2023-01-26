#pragma once

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct emptyStackException : public std::exception {
    const char* what() const throw();
};

template <typename T>
class SafeStack {
public:
    SafeStack() = default;
    SafeStack(SafeStack const& rhs) {
        std::lock_guard<std::mutex> lg{rhs.m};
        data = rhs.data;
    }
    SafeStack& operator=(SafeStack const&) = delete;

    void push(T newValue) {
        std::lock_guard<std::mutex> l{m};
        data.push(newValue);
    }
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> l{m};
        if(data.empty()) throw emptyStackException();
        std::shared_ptr<T> const res { std::make_shared<T>(data.top())};
        data.pop();
        return res;
    }
    void pop(T& value) {
        std::lock_guard<std::mutex> l{m};
        if(data.empty()) throw emptyStackException();
        value = data.top();
        data.pop();
    }
    bool empty() const {
        std::lock_guard<std::mutex> l{m};
        return data.empty();
    }
private:
    std::stack<T> data;
    mutable std::mutex m;
};