#include "Jalousie.h"

Jalousie::Jalousie(int controllerToListenTo, std::chrono::milliseconds jalousieStatusPrintInterval)
	: CustomConsumer::CustomConsumer(std::vector<std::string>{"JalousieController" + std::to_string(controllerToListenTo)}), CustomThread::CustomThread(jalousieStatusPrintInterval) {}

void Jalousie::threadTask() {
	std::cout << "Jalousie is currently ";
	if (m_jalousieStatus < 0.0) {
		std::cout << "broken." << std::endl;
	} else if (m_jalousieStatus < 0.01) {
		std::cout << "open." << std::endl;
	} else {
		std::cout << "closed by " << std::to_string((int)(m_jalousieStatus * 100)) << "%." << std::endl;
	}
}

void Jalousie::notify(std::string producerID, std::string msg) {
	m_jalousieStatus = strtod(msg.c_str(), nullptr);
}