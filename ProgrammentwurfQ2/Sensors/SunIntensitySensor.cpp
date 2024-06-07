#include "SunIntensitySensor.h"

SunIntensitySensor::SunIntensitySensor(int sunIntensitySensorID, Umwelt* pUmwelt)
	: UmweltSensor::UmweltSensor("SunIntensitySensor" + std::to_string(sunIntensitySensorID), pUmwelt) {}

void SunIntensitySensor::measure() {
	m_sensorValue = getUmwelt()->getSunIntensity();
}
