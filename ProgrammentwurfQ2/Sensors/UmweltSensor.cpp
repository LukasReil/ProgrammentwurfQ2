#include "UmweltSensor.h"


UmweltSensor::UmweltSensor(std::string name, Umwelt* pUmwelt)
	: Sensor::Sensor(name), m_pUmwelt(pUmwelt) {}

Umwelt* UmweltSensor::getUmwelt() {
	return m_pUmwelt;
}