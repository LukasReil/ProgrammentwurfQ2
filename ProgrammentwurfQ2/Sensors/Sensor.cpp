#include "Sensor.h"

Sensor::Sensor(std::string name)
	: Producer::Producer(name), m_sensorValue(0) {}


/*
* Sends the measured value to the dispatcher. The double is converted to a string
*
* @return the sent sensor value as a string
*/
std::string Sensor::send() {
	return std::to_string(m_sensorValue);
}

