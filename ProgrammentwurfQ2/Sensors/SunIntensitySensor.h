#pragma once

#include "../api/Umwelt.h"

#include "UmweltSensor.h"

class SunIntensitySensor : public UmweltSensor {
public:
	SunIntensitySensor(int sunIntensitySensorID, Umwelt* pUmwelt);
	virtual void measure();
};