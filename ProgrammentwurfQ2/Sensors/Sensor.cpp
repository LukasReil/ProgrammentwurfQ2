#include "Sensor.h"

Sensor::Sensor(std::string name, Umwelt* pUmwelt)
	: Producer::Producer(name), m_sensorValue(0), m_pUmwelt(pUmwelt) {
}

std::string Sensor::send() {
	return std::to_string(m_sensorValue);
}
