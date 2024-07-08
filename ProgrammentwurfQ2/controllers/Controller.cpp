#include "Controller.h"

Controller::Controller(std::string producerID, std::vector<std::string> toRegisterToProducers)
	: Producer::Producer(producerID), CustomConsumer::CustomConsumer(toRegisterToProducers) {}

/*
* Registers the internal consumer at the supplied dispatcher and subcribes to producers
* Additionally also registers the internal producer
* 
* @param pDispatcher:	The dispatcher the controller should register at
*/
void Controller::registerAtDispatcher(Dispatcher* pDispatcher) {
	CustomConsumer::registerAtDispatcher(pDispatcher);
	pDispatcher->registerProducer(this);
}

/*
* Pre-Registers the internal consumer at the supplied dispatcher and pre-subcribes to producers
* Additionally also registers the internal producer
* Actual registration happens later by the dispatcher itself, to avoid any cross-dependencies by intertalking controllers
*
* @param pCustomDispatcher:	The custom dispatcher the controller should pre-register at
*/
void Controller::preRegisterAtCustomDispatcher(CustomDispatcher* pCustomDispatcher) {
	CustomConsumer::preRegisterAtCustomDispatcher(pCustomDispatcher);
	pCustomDispatcher->preRegisterProducer(this);
}
