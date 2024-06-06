#include "OutsideTemperatureSensor.h"

OutsideTemperatureSensor::OutsideTemperatureSensor(int outsideTemperatureSensorID, Umwelt* pUmwelt)
	: Sensor::Sensor("OutsideTemperatureSensor" + std::to_string(outsideTemperatureSensorID), pUmwelt)
{
}

void OutsideTemperatureSensor::measure()
{
	m_sensorValue = m_pUmwelt->getOutsideTemp();
}
