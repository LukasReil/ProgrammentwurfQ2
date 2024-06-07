#pragma once

#include <chrono>
#include <atomic>
#include <iostream>
#include <string>

#include "../api/Dispatcher.h"

#include "../apiWrapper/CustomConsumer.h"
#include "../multithreading/CustomThread.h"

class Jalousie : public CustomConsumer, public CustomThread {
public:
	Jalousie(int controllerToListenTo, std::chrono::milliseconds jalousieStatusPrintInterval);
	virtual void threadTask();
	virtual void notify(std::string producerID, std::string msg);
private:
	//1: Closed 0: Open
	std::atomic<double> m_jalousieStatus;
};