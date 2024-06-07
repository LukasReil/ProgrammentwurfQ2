#pragma once

#include "../api/Umwelt.h"

#include "Sensor.h"

class OutsideTemperatureSensor : public Sensor {
public:
	OutsideTemperatureSensor(int outsideTemperatureSensorID, Umwelt* pUmwelt);
	virtual void measure();

};