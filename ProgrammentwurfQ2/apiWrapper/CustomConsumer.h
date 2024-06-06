#pragma once

#include <vector>
#include <string>

#include "../api/Consumer.h"
#include "../api/Dispatcher.h"

class CustomConsumer : public Consumer {
public:
	CustomConsumer(std::vector<std::string> toRegisterToProducers);
	virtual void notify(std::string producerId, std::string msg) = 0;
	void registerAtDispatcher(Dispatcher* pDispatcher);
private:
	std::vector<std::string> m_toRegisterToProducers;
};