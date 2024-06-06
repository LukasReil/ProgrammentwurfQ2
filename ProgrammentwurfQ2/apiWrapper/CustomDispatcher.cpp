#include "CustomDispatcher.h"

CustomDispatcher::CustomDispatcher(std::chrono::milliseconds dispatchInterval)
	: Dispatcher::Dispatcher(), m_dispatchInterval(dispatchInterval){
}

void CustomDispatcher::run(CustomDispatcher* pSelf) {

	pSelf->m_running = true;
	while (!pSelf->m_shutdown) {
		// Does the magic
		pSelf->dispatchMessages();

		// Lets Dispatcher sleep for a second
		this_thread::sleep_for(pSelf->m_dispatchInterval);
	}
	pSelf->m_running = false;
}

void CustomDispatcher::startThread() {
	m_shutdown = false;
	std::thread thread(run, this);
	thread.detach();
}

void CustomDispatcher::stopThread() {
	m_shutdown = true;
	while (m_running);
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
