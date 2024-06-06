#pragma once


#include <string>
#include <atomic>

#include "../api/Producer.h"
#include "../api/Umwelt.h"

class Sensor : public Producer {
public:
	Sensor(std::string name, Umwelt* pUmwelt);
	virtual void measure() = 0;
	virtual std::string send();
protected:
	std::atomic<double> m_sensorValue;
	Umwelt* m_pUmwelt;
};