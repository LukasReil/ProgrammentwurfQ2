#include "SensorMeasureThread.h"

SensorMeasureThread::SensorMeasureThread(const std::vector<Sensor*>& sensors, std::chrono::milliseconds measureInterval)
	: m_sensors(sensors), m_measureInterval(measureInterval)
{
}


void SensorMeasureThread::run(SensorMeasureThread* pSelf) {

	pSelf->m_running = true;
	while (!pSelf->m_shutdown) {
		for (Sensor* pSensor : pSelf->m_sensors) {
			pSensor->measure();
		}

		this_thread::sleep_for(pSelf->m_measureInterval);
	}
	pSelf->m_running = false;
}

void SensorMeasureThread::startThread() {
	m_shutdown = false;
	std::thread thread(run, this);
	thread.detach();
}

void SensorMeasureThread::stopThread() {
	m_shutdown = true;
	while (m_running);
}