#pragma once
#include <Utils.hpp>
#include <thread>
#include <vector>
#include <functional>
#include <algorithm>

class ThreadPool final {
public:
	ThreadPool() = default;		
	template <typename Function, typename ... Args >
	void spawn(Function&& func, Args ... args) {
		mPool.emplace_back(std::forward<Function>(func), std::forward<Args>(args)...);
	}
	~ThreadPool() {
		std::for_each(mPool.begin(), mPool.end(),
			std::mem_fn(&std::thread::join));
	}	
private:
	std::vector<std::thread> mPool{};
};
