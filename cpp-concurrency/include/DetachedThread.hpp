#pragma once
#include <thread>

class DetachedThread final : private NonCopyable {
public:
    template <typename Func, typename ... Args>
    explicit DetachedThread(Func f, Args&& ... args) 
    : t{std::forward<Func>(f), std::forward<Args>(args)...}
    {
        if(t.joinable())
            t.detach();
    }
    ~DetachedThread() = default;
private:
    std::thread t;
};
