#pragma once

#include <thread>
#include <chrono>
#include <atomic>

/*
* A implementation to allow for easy mulithreading.
* All classes inheriting from this class need to implement "threadTask()",
* which is the task executed by the thread every execution Interval.
*/
class CustomThread {
public:
	CustomThread(std::chrono::milliseconds executionInterval);
	~CustomThread();
	virtual void threadTask() = 0;
	virtual void startThread();
	virtual void stopThread();
private:
	static void run(CustomThread* pSelf);
	std::atomic_bool m_shutdown{ true };
	std::atomic_bool m_running{ false };
	std::chrono::milliseconds m_executionInterval;
};