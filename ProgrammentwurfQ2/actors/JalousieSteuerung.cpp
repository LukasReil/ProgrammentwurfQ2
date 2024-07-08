#include "JalousieSteuerung.h"

JalousieSteuerung::JalousieSteuerung(int controllerToListenTo, int jalousieID, std::chrono::milliseconds jalousieStatusPrintInterval)
	:	CustomConsumer::CustomConsumer(std::vector<std::string>{"JalousieController" + std::to_string(controllerToListenTo)}), 
		Sensor::Sensor("JalousieSensor" + std::to_string(jalousieID)), 
		CustomThread::CustomThread(jalousieStatusPrintInterval) {}

/*
* Prints the status of the Jalousie to the console every x milliseconds
*/
void JalousieSteuerung::threadTask() {
	//Preparing String before printing, as multithreading may interfere with printing
	std::string out = "Jalousie is currently ";
	if (m_jalousieStatus < 0.0) {
		out += "broken.\n";
	} else if (m_jalousieStatus < 0.01) {
		out += "open.\n";
	} else {
		out += "closed by " + std::to_string((int)(m_jalousieStatus * 100)) + "%.\n";
	}
	std::cout << out;
}

/*
* Sets the jalousie sensor's meassured value to the current closed status in percent 
*/
void JalousieSteuerung::measure() {
	m_sensorValue = (double) m_jalousieStatus * 100;
}

/*
* Receives notifications from the dispatcher.
* Received notifications come from the jalousie controller to regulate how far the jalousie is opened or closed
* 
* @param producerID:	ID of the sending producer (Jalousie Controller)
* @param msg:			Message from producer (Wanted status of the Jalousie)
*/
void JalousieSteuerung::notify(std::string producerID, std::string msg) {
	std::string o = "Jalousie is set to " + msg + " by Dispatcher\n";
	//std::cout << o;
	m_jalousieStatus = strtod(msg.c_str(), nullptr);
}

/*
* Pre-Registers the internal consumer at the supplied dispatcher and pre-subcribes to producers
* Additionally also registers the internal producer
* Actual registration happens later by the dispatcher itself, to avoid any cross-dependencies by intertalking controllers
*
* @param pCustomDispatcher:	The custom dispatcher the Jalousie Steuerung should pre-register at
*/
void JalousieSteuerung::preRegisterAtCustomDispatcher(CustomDispatcher* pCustomDispatcher) {
	CustomConsumer::preRegisterAtCustomDispatcher(pCustomDispatcher);
	pCustomDispatcher->preRegisterProducer(this);
}
