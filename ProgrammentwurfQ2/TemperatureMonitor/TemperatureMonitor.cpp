#include "TemperatureMonitor.h"

const std::string TemperatureMonitor::outsideTemperatureSensorID{ "OutsideTemperatureSensor0" };
const std::string TemperatureMonitor::insideTemperatureSensorID{ "InsideTemperatureSensor0" };

TemperatureMonitor::TemperatureMonitor(std::chrono::milliseconds printInterval)
	: CustomThread::CustomThread(printInterval), CustomConsumer::CustomConsumer(std::vector<std::string>{outsideTemperatureSensorID, insideTemperatureSensorID}) {}

TemperatureMonitor::~TemperatureMonitor() {
	stopThread();
}

void TemperatureMonitor::notify(std::string producerID, std::string msg) {

	double msgDouble = strtod(msg.c_str(), nullptr);

	if (producerID == outsideTemperatureSensorID) {
		m_outsideTemperature = msgDouble;
	}
	else if (producerID == insideTemperatureSensorID) {
		m_insideTemperature = msgDouble;
	}
}

void TemperatureMonitor::threadTask() {
	std::cout << "Outside Temperature: " << m_outsideTemperature << "*C" << std::endl;
	std::cout << "Inside Temperature:  " << m_outsideTemperature << "*C" << std::endl;
}
