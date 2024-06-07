#pragma once

#include <chrono>
#include <atomic>
#include <iostream>
#include <string>

#include "../api/Dispatcher.h"

#include "../apiWrapper/CustomConsumer.h"
#include "../multithreading/CustomThread.h"
#include "../Sensors/Sensor.h"

class JalousieSteuerung : public CustomConsumer, public Sensor, public CustomThread {
public:
	JalousieSteuerung(int controllerToListenTo, int jalousieID, std::chrono::milliseconds jalousieStatusPrintInterval);
	virtual void threadTask();
	virtual void measure();
	virtual void notify(std::string producerID, std::string msg);
private:
	//1: Closed 0: Open
	std::atomic<double> m_jalousieStatus;
};