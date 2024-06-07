#pragma once


#include "../api/Umwelt.h"

#include "Sensor.h"

class UmweltSensor : public Sensor {
public:
	UmweltSensor(std::string name, Umwelt* pUmwelt);
	Umwelt* getUmwelt();
private:
	Umwelt* m_pUmwelt;
};