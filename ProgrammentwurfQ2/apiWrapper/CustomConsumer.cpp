#include "CustomConsumer.h"

CustomConsumer::CustomConsumer(std::vector<std::string> toRegisterToProducers)
	: m_toRegisterToProducers(toRegisterToProducers) {}

void CustomConsumer::registerAtDispatcher(Dispatcher* pDispatcher) {
	for (std::string producerID : m_toRegisterToProducers) {
		if (!pDispatcher->subscribe(producerID, this)) {
			throw "Could not register to producer " + producerID + ".  Is the ID spelled correctly?";
		}
	}
}
