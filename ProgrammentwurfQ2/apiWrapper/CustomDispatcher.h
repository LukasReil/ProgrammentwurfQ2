#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <atomic>
#include <exception>
#include <chrono>
#include <iostream>

#include "../api/Dispatcher.h"
#include "../api/Consumer.h"
#include "../api/Producer.h"

#include "../multithreading/CustomThread.h"

/*
* Custom Wrapper for abstract Dispatcher Class
* Extends CustomThread class, to run dispatchMessages() async
*/
class CustomDispatcher : public Dispatcher, public CustomThread {
public:
	class SubscriptionException : public std::exception {
	public:
		SubscriptionException(const std::string& notFoundProducer) 
			: m_notFoundProducer(notFoundProducer) {}
		void print() {
			std::cout << "Could not subscribe a Consumer to Producer \"" << m_notFoundProducer << "\"!" << std::endl;
		}
	private:
		std::string m_notFoundProducer;
	};
	CustomDispatcher(std::chrono::milliseconds dispatchInterval);
	void preRegisterProducer(Producer* pProducer);
	void preRegisterConsumer(std::string toSubscribeToProducerId, Consumer* pConsumer);
	void preRegisterConsumer(std::vector<std::string> toSubscribeToProducerIds, Consumer* pConsumer);
	void registerPreRegisteredProducersAndConsumers();
	virtual void startThread() override;
	virtual void threadTask();
	virtual bool registerProducer(Producer* pProducer);
	virtual bool subscribe(std::string producerId, Consumer* pConsumer);
	virtual void dispatchMessages();

private:
	std::unordered_map<Consumer*, std::vector<std::string>> m_consumerProducerPairs;
	std::unordered_map<std::string, Producer*> m_registeredProducers;
	std::unordered_map<Consumer*, std::vector<std::string>> m_preRegisteredConsumerProducerPairs;
	std::vector<Producer*> m_preRegisteredProducers;
};