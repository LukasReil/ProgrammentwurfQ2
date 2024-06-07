#pragma once

#include "../api/Umwelt.h"

#include "Sensor.h"

class InsideTemperatureSensor : public Sensor {
public:
	InsideTemperatureSensor(int insideTemperatureSensorID, Umwelt* pUmwelt);
	virtual void measure();
};