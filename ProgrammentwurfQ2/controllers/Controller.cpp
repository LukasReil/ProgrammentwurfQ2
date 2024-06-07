#include "Controller.h"

Controller::Controller(std::string producerID, std::vector<std::string> toRegisterToProducers)
	: Producer::Producer(producerID), CustomConsumer::CustomConsumer(toRegisterToProducers) {}

void Controller::registerAtDispatcher(Dispatcher* pDispatcher)
{
	CustomConsumer::registerAtDispatcher(pDispatcher);
	pDispatcher->registerProducer(this);
}
