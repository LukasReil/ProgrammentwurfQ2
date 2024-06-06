#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

#include "../api/Dispatcher.h"
#include "../multithreading/CustomThread.h"

class CustomDispatcher : public Dispatcher, public CustomThread {
public:
	CustomDispatcher(std::chrono::milliseconds dispatchInterval);
	virtual void threadTask();
	virtual bool registerProducer(Producer* pProducer);
	virtual bool subscribe(std::string producerId, Consumer* pConsumer);
	virtual void dispatchMessages();

private:
	std::unordered_map<Consumer*, std::vector<std::string>> m_consumerProducerPairs;
	std::unordered_map<std::string, Producer*> m_registeredProducers;
};