#pragma once

#include <thread>
#include <atomic>
#include <iostream>
#include <chrono>

#include "../api/Dispatcher.h"
#include "../apiWrapper/CustomConsumer.h"
#include "../multithreading/CustomThread.h"

class TemperatureMonitor : public CustomConsumer, public CustomThread {
public:
	TemperatureMonitor(std::chrono::milliseconds printInterval);
	~TemperatureMonitor();
	virtual void notify(std::string producerID, std::string msg);
	virtual void threadTask();
private:
	std::atomic<double> m_outsideTemperature{ 0 };
	std::atomic<double> m_insideTemperature{ 0 };
	static const std::string outsideTemperatureSensorID;
	static const std::string insideTemperatureSensorID;
};