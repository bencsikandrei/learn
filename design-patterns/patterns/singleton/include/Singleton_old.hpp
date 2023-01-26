#pragma once

#include <mutex>
/*
 * Old style singleton, with double IF for thread safety
 */
class Singleton {
public:
	static Singleton& get();
private:
	Singleton() = default;
	~Singleton() = default;
	Singleton(Singleton const& rhs) = delete;
	Singleton& operator=(Singleton const& rhs) = delete;

	static Singleton* instance;
	static std::mutex singletonLock;
};
