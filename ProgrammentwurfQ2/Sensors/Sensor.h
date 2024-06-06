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
	Umwelt* getUmwelt();
protected:
	//Measured sensor Value. Set by the actual Sensor Implementation
	std::atomic<double> m_sensorValue;
private:
	Umwelt* m_pUmwelt;
};