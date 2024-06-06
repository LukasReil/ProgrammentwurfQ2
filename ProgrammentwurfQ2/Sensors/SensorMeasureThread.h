#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include "Sensor.h"
#include "../multithreading/CustomThread.h"

class SensorMeasureThread : public CustomThread {
public:
	SensorMeasureThread(const std::vector<Sensor*>& sensors, std::chrono::milliseconds measureInterval);
	virtual void threadTask();
private:
	std::vector<Sensor*> m_sensors;
};