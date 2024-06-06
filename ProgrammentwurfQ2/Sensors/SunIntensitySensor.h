#pragma once

#include "Sensor.h"

class SunIntensitySensor : public Sensor {
public:
	SunIntensitySensor(int sunIntensitySensorID, Umwelt* pUmwelt);
	virtual void measure();
};