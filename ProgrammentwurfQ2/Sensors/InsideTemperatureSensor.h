#pragma once

#include "../api/Umwelt.h"

#include "UmweltSensor.h"

class InsideTemperatureSensor : public UmweltSensor {
public:
	InsideTemperatureSensor(int insideTemperatureSensorID, Umwelt* pUmwelt);
	virtual void measure();
};