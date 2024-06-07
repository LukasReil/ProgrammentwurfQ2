#pragma once

#include <string>
#include <atomic>

#include "../api/Producer.h"

class Sensor : public Producer {
public:
	Sensor(std::string name);
	virtual void measure() = 0;
	virtual std::string send();
protected:
	//Measured sensor Value. Set by the actual Sensor Implementation
	std::atomic<double> m_sensorValue;
};