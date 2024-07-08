#include "CustomConsumer.h"

CustomConsumer::CustomConsumer(std::vector<std::string> toRegisterToProducers)
	: m_toRegisterToProducers(toRegisterToProducers) {}

/*
* Registers the consumer at the supplied dispatcher and subcribes to producers
* 
* @param pDispatcher:	The dispatcher the consumer should register at
* 
* @throws std::string if consumer can't register at any wanted producer
*/
void CustomConsumer::registerAtDispatcher(Dispatcher* pDispatcher) {
	for (std::string producerID : m_toRegisterToProducers) {
		if (!pDispatcher->subscribe(producerID, this)) {
			throw "Could not register to producer " + producerID + ".  Is the ID spelled correctly?";
		}
	}
}

/*
* Pre registers Consumer at Custom Dispatcher as a part of the centralized registration pipeline
* 
* @param pCustomDispatcher:	The Custom Dispatcher to register at
*/
void CustomConsumer::preRegisterAtCustomDispatcher(CustomDispatcher* pCustomDispatcher) {
	for (std::string producerID : m_toRegisterToProducers) {
		pCustomDispatcher->preRegisterConsumer(producerID, this);
	}
}
