#include "TemperatureMonitor.h"

const std::string TemperatureMonitor::outsideTemperatureSensorID{ "OutsideTemperatureSensor0" };
const std::string TemperatureMonitor::insideTemperatureSensorID{ "InsideTemperatureSensor0" };

TemperatureMonitor::TemperatureMonitor(std::chrono::milliseconds printInterval)
	: m_printInterval(printInterval) {
}

TemperatureMonitor::~TemperatureMonitor() {
	stopThread();
}

void TemperatureMonitor::notify(std::string producerID, std::string msg) {

	double msgDouble = strtod(msg.c_str(), nullptr);

	//std::cout << "Msg from " << producerID << ": \"" << msg << "\"" << std::endl;

	if (producerID == outsideTemperatureSensorID) {
		m_outsideTemperature = msgDouble;
	}
	else if (producerID == insideTemperatureSensorID) {
		m_insideTemperature = msgDouble;
	}
}

void TemperatureMonitor::registerAtDispatcher(Dispatcher* pDispatcher) {
	if (!pDispatcher->subscribe(outsideTemperatureSensorID, this) || !pDispatcher->subscribe(insideTemperatureSensorID, this)) {
		throw "TemperatureMonitor failed to subscribe to Temperature Sensors! Are the IDs spelled correctly?";
	}
}

void TemperatureMonitor::startThread() {
	m_shutdown = false;
	std::thread thread(run, this);
	thread.detach();
}

void TemperatureMonitor::stopThread() {
	m_shutdown = true;
	while (m_running);
}

void TemperatureMonitor::run(TemperatureMonitor* pSelf) {
	pSelf->m_running = true;
	while (!pSelf->m_shutdown) {

		std::cout << "Outside Temperature: " << pSelf->m_outsideTemperature << "*C" << std::endl;
		std::cout << "Inside Temperature:  " << pSelf->m_outsideTemperature << "*C" << std::endl;

		std::this_thread::sleep_for(pSelf->m_printInterval);
	}
	pSelf->m_running = false;
}
