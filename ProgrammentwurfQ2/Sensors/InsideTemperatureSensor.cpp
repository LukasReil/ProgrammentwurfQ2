#include "InsideTemperatureSensor.h"

InsideTemperatureSensor::InsideTemperatureSensor(int insideTemperatureSensorID, Umwelt* pUmwelt)
	: UmweltSensor::UmweltSensor("InsideTemperatureSensor" + std::to_string(insideTemperatureSensorID), pUmwelt) {
}

void InsideTemperatureSensor::measure() {
	m_sensorValue = getUmwelt()->getInsideTemp();
}
