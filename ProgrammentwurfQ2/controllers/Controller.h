#pragma once

#include <vector>
#include <string>

#include "../api/Producer.h"

#include "../apiWrapper/CustomConsumer.h"

class Controller : public Producer, public CustomConsumer {
public:
	Controller(std::string producerID, std::vector<std::string> toRegisterToProducers);
	virtual void notify(std::string producerID, std::string msg) = 0;
	virtual void registerAtDispatcher(Dispatcher* pDispatcher) override;
	virtual std::string send() = 0;
};