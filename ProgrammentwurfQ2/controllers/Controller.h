#pragma once

#include <vector>
#include <string>

#include "../api/Producer.h"

#include "../apiWrapper/CustomConsumer.h"
#include "../apiWrapper/CustomDispatcher.h"

/*
* Wrapper class to implement a Controller
* Wraps a Producer and a Custom Consumer in one class
* Overrides the registerAtDispatcher function to also register its internal Producer
*/
class Controller : public Producer, public CustomConsumer {
public:
	Controller(std::string producerID, std::vector<std::string> toRegisterToProducers);
	virtual void notify(std::string producerID, std::string msg) = 0;
	virtual void registerAtDispatcher(Dispatcher* pDispatcher) override;
	virtual void preRegisterAtCustomDispatcher(CustomDispatcher* pCustomDispatcher) override;
	virtual std::string send() = 0;
};