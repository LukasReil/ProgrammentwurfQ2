#include "SensorMeasureThread.h"

SensorMeasureThread::SensorMeasureThread(const std::vector<Sensor*>& sensors, std::chrono::milliseconds measureInterval)
	: CustomThread::CustomThread(measureInterval), m_sensors(sensors) {}

void SensorMeasureThread::threadTask() {

	for (Sensor* pSensor : m_sensors) {
		pSensor->measure();
	}

}