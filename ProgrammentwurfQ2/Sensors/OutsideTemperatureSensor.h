#pragma once

#include "../api/Umwelt.h"

#include "UmweltSensor.h"

class OutsideTemperatureSensor : public UmweltSensor {
public:
	OutsideTemperatureSensor(int outsideTemperatureSensorID, Umwelt* pUmwelt);
	virtual void measure();

};