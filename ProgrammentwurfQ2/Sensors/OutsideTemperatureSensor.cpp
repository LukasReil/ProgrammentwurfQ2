#include "OutsideTemperatureSensor.h"

OutsideTemperatureSensor::OutsideTemperatureSensor(int outsideTemperatureSensorID, Umwelt* pUmwelt)
	: UmweltSensor::UmweltSensor("OutsideTemperatureSensor" + std::to_string(outsideTemperatureSensorID), pUmwelt) {}

void OutsideTemperatureSensor::measure() {
	m_sensorValue = getUmwelt()->getOutsideTemp();
}
