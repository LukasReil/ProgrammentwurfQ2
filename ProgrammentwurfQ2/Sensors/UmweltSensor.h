#pragma once


#include "../api/Umwelt.h"

#include "Sensor.h"
/*
* A wrapper for all Sensors requiring an instance of the Umwelt to function correctly
*/
class UmweltSensor : public Sensor {
public:
	UmweltSensor(std::string name, Umwelt* pUmwelt);
	Umwelt* getUmwelt();
private:
	Umwelt* m_pUmwelt;
};