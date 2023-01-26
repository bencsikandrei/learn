#include <Singleton_old.hpp>
#include <iostream>
#include <mutex>

Singleton& Singleton::get() {
	std::lock_guard<std::mutex> lock(singletonLock);
	if(not instance) {
		instance = new Singleton;
	}
	return *instance;
}

Singleton* Singleton::instance{nullptr};
std::mutex Singleton::singletonLock{};
