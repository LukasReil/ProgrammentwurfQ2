#pragma once

#include <vector>
#include <string>

#include "../api/Consumer.h"
#include "../api/Dispatcher.h"
#include "../apiWrapper/CustomDispatcher.h"
/*
* Custom Consumer class to wrap the abstract Consumer and supply additional functionality
* like unifying the subscription process
*/
class CustomConsumer : public Consumer {
public:
	CustomConsumer(std::vector<std::string> toRegisterToProducers);
	virtual void notify(std::string producerId, std::string msg) = 0;
	virtual void registerAtDispatcher(Dispatcher* pDispatcher);
	virtual void preRegisterAtCustomDispatcher(CustomDispatcher* pCustomDispatcher);
private:
	std::vector<std::string> m_toRegisterToProducers;
};