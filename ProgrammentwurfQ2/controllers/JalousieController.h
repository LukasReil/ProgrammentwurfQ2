#pragma once

#include <string>
#include <atomic>

#include "../api/Producer.h"
#include "../api/Dispatcher.h"
#include "../apiWrapper/CustomConsumer.h"


class JalousieController : public Producer, public CustomConsumer {
public:
	JalousieController(int jalousieControllerID);
	virtual void notify(std::string producerID, std::string msg);
	virtual std::string send();

private:
	std::atomic<double> m_sunIntensity{ 0 };
	std::atomic<double> m_insideTemperature{ 0 };
	std::atomic<double> m_calculatedJalousieStatus{ 1 };
	static const std::string sunIntensitySensorID;
	static const std::string insideTemperatureSensorID;
};