#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

#include "../api/Dispatcher.h"

class CustomDispatcher : public Dispatcher {
public:
	CustomDispatcher(std::chrono::milliseconds dispatchInterval);
	static void run(CustomDispatcher* pSelf);
	void startThread();
	void stopThread();
	virtual bool registerProducer(Producer* pProducer);
	virtual bool subscribe(std::string producerId, Consumer* pConsumer);
	virtual void dispatchMessages();

private:
	std::unordered_map<Consumer*, std::vector<std::string>> m_consumerProducerPairs;
	std::unordered_map<std::string, Producer*> m_registeredProducers;
	std::atomic_bool m_shutdown{ true };
	std::atomic_bool m_running{ false };
	std::chrono::milliseconds m_dispatchInterval;
};