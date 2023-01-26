#pragma once

class SingletonNew {
public:
	static SingletonNew& get() {
		static SingletonNew instance;
		return instance;
	}

private:
	SingletonNew() = default;
	SingletonNew(SingletonNew const& rhs) = default;
	SingletonNew& operator=(SingletonNew const& rhs) = delete;
	SingletonNew& operator=(SingletonNew && rhs) = delete;
};
