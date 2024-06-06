#include "InsideTemperatureSensor.h"

InsideTemperatureSensor::InsideTemperatureSensor(int insideTemperatureSensorID, Umwelt* pUmwelt)
	: Sensor::Sensor("InsideTemperatureSensor" + std::to_string(insideTemperatureSensorID), pUmwelt) {
}

void InsideTemperatureSensor::measure() {
	m_sensorValue = getUmwelt()->getInsideTemp();
}
