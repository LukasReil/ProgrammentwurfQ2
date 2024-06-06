#include "CustomDispatcher.h"

CustomDispatcher::CustomDispatcher(std::chrono::milliseconds dispatchInterval)
	: Dispatcher::Dispatcher(), CustomThread::CustomThread(dispatchInterval) {}

void CustomDispatcher::threadTask() {
	dispatchMessages();
}

bool CustomDispatcher::registerProducer(Producer* pProducer) {
	std::string producerID = pProducer->getId();
	if (m_registeredProducers.contains(producerID)) {
		return false;
	}
	m_registeredProducers[producerID] = pProducer;
	return true;
}

bool CustomDispatcher::subscribe(std::string producerId, Consumer* pConsumer) {

	if (!m_registeredProducers.contains(producerId)) {
		return false;
	}

	m_consumerProducerPairs[pConsumer].push_back(producerId);

	return true;
}

void CustomDispatcher::dispatchMessages() {
	std::unordered_map<std::string, std::string> receivedMessages;

	for (auto producer = m_registeredProducers.begin(); producer != m_registeredProducers.end(); producer++) {
		receivedMessages[producer->first] = producer->second->send();
	}

	for (auto consumer = m_consumerProducerPairs.begin(); consumer != m_consumerProducerPairs.end(); consumer++) {
		for (const std::string& producerID : consumer->second) {
			consumer->first->notify(producerID, receivedMessages[producerID]);
		}
	}
}
