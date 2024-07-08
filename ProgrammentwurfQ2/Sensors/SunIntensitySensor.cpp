#include "SunIntensitySensor.h"

SunIntensitySensor::SunIntensitySensor(int sunIntensitySensorID, Umwelt* pUmwelt)
	: UmweltSensor::UmweltSensor("SunIntensitySensor" + std::to_string(sunIntensitySensorID), pUmwelt) {}

void SunIntensitySensor::measure() {
	//The Umwelt.getSunIntensity() function is broken and returns values from -860% to 940%
	m_sensorValue = getUmwelt()->getSunIntensity();
}
