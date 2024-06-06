#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include "Sensor.h"

class SensorMeasureThread {
public:
	SensorMeasureThread(const std::vector<Sensor*>& sensors, std::chrono::milliseconds measureInterval);
	static void run(SensorMeasureThread* pSelf);
	void startThread();
	void stopThread();
private:
	std::atomic_bool m_shutdown{ true };
	std::atomic_bool m_running{ false };
	std::chrono::milliseconds m_measureInterval;
	std::vector<Sensor*> m_sensors;
};