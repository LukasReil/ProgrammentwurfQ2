#include "Sensor.h"

Sensor::Sensor(std::string name)
	: Producer::Producer(name), m_sensorValue(0) {}

std::string Sensor::send() {
	return std::to_string(m_sensorValue);
}

