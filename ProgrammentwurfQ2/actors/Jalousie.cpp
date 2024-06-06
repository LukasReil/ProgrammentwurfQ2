#include "Jalousie.h"

Jalousie::Jalousie(int controllerToListenTo, std::chrono::milliseconds jalousieStatusPrintInterval)
	: CustomConsumer::CustomConsumer(std::vector<std::string>{"JalousieController" + std::to_string(controllerToListenTo)}), CustomThread::CustomThread(jalousieStatusPrintInterval) {}

void Jalousie::threadTask() {
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

void Jalousie::notify(std::string producerID, std::string msg) {
	m_jalousieStatus = strtod(msg.c_str(), nullptr);
}