#pragma once

#include <thread>
#include <atomic>
#include <iostream>
#include <chrono>

#include "../api/Dispatcher.h"
#include "../api/Consumer.h"

class TemperatureMonitor : public Consumer {
public:
	TemperatureMonitor(std::chrono::milliseconds printInterval);
	~TemperatureMonitor();
	virtual void notify(std::string producerID, std::string msg);
	void registerAtDispatcher(Dispatcher* pDispatcher);
	void startThread();
	void stopThread();
private:
	static void run(TemperatureMonitor* pSelf);
	std::chrono::milliseconds m_printInterval{ 0 };
	std::atomic<double> m_outsideTemperature{ 0 };
	std::atomic<double> m_insideTemperature{ 0 };
	std::atomic_bool m_shutdown{ true };
	std::atomic_bool m_running{ false };
	static const std::string outsideTemperatureSensorID;
	static const std::string insideTemperatureSensorID;
};