#pragma once

#include <thread>
#include <chrono>
#include <atomic>

class CustomThread {
public:
	CustomThread(std::chrono::milliseconds executionInterval);
	~CustomThread();
	virtual void threadTask() = 0;
	void startThread();
	void stopThread();
private:
	static void run(CustomThread* pSelf);
	std::atomic_bool m_shutdown{ true };
	std::atomic_bool m_running{ false };
	std::chrono::milliseconds m_executionInterval;
};