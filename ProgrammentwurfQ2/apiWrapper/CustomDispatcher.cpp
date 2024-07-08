#include "CustomDispatcher.h"

CustomDispatcher::CustomDispatcher(std::chrono::milliseconds dispatchInterval)
	: Dispatcher::Dispatcher(), CustomThread::CustomThread(dispatchInterval) {}

/*
* Pre registers Producer at Dispatcher for centralized registration process
*/
void CustomDispatcher::preRegisterProducer(Producer* pProducer) {
	m_preRegisteredProducers.push_back(pProducer);
}

/*
* Pre registers consumer at Dispatcher for centralized registration process.
* Allows for two Controllers to register after each other without causing problems.
* 
* @param toSubscribeToProducerId:	One producer the consumer wants to subscribe to
* @param pConsumer:					The subscribing consumer
* 
*/
void CustomDispatcher::preRegisterConsumer(std::string toSubscribeToProducerId, Consumer* pConsumer) {
	if (m_preRegisteredConsumerProducerPairs.contains(pConsumer)) {
		m_preRegisteredConsumerProducerPairs[pConsumer].push_back(toSubscribeToProducerId);
	}
	else {
		m_preRegisteredConsumerProducerPairs[pConsumer] = std::vector<std::string>({ toSubscribeToProducerId });
	}
}

/*
* Pre registers consumer at Dispatcher for centralized registration process.
* Allows for two Controllers to register after each other without causing problems.
* Allows a consumer to subscribe to multiple producers at once
* 
* @param toSubscribeToProducerIds:	Some producers the consumer wants to subscribe to
* @param pConsumer:					The subscribing consumer
* 
*/
void CustomDispatcher::preRegisterConsumer(std::vector<std::string> toSubscribeToProducerIds, Consumer* pConsumer) {
	if (m_preRegisteredConsumerProducerPairs.contains(pConsumer)) {
		m_preRegisteredConsumerProducerPairs[pConsumer].insert(m_preRegisteredConsumerProducerPairs[pConsumer].end(), toSubscribeToProducerIds.begin(), toSubscribeToProducerIds.end());
	}
	else {
		m_preRegisteredConsumerProducerPairs[pConsumer] = toSubscribeToProducerIds;
	}
}

/*
* Main function of centralized registration process.
* Registers all pre-registered Producers and subscribes to them afterwards with respective consumers
* No collision between inter-talking controllers
* 
* @throws SubscriptionException:	If one consumer can't subscribe to producer
*/
void CustomDispatcher::registerPreRegisteredProducersAndConsumers() {
	for (auto producer : m_preRegisteredProducers) {
		registerProducer(producer);
	}
	m_preRegisteredProducers.clear();
	for (auto consumer : m_preRegisteredConsumerProducerPairs) {
		for (auto toSubscribeTo : consumer.second) {
			if (!subscribe(toSubscribeTo, consumer.first)) {
				throw SubscriptionException(toSubscribeTo);
			}
		}
	}
	m_preRegisteredConsumerProducerPairs.clear();
}

/*
* Registers all pre-registered Producers and Consumers before starting Dispatcher thread
*/
void CustomDispatcher::startThread() {
	registerPreRegisteredProducersAndConsumers();
	CustomThread::startThread();
}

/*
* Task performed by thread: dispatch Messages until thread is stopped
*/
void CustomDispatcher::threadTask() {
	dispatchMessages();
}

/*
* Registers producer at dispatcher
* 
* @param pProducer: Pointer to producer, that shall be registered
* 
* @return	true if no producer with the same ID was found and new producer was registered.
*			false otherwise
*/
bool CustomDispatcher::registerProducer(Producer* pProducer) {
	std::string producerID = pProducer->getId();
	if (m_registeredProducers.contains(producerID)) {
		return false;
	}
	m_registeredProducers[producerID] = pProducer;
	return true;
}

/*
* Let's a consumer subscribe a producer
*
* @param producerId:	The ID of the producer the consumer wants to subscribe to
* @param pConsumer:		Pointer to consumer, that wants to subscribe
*
* @return	true if a producer with the supplied ID was found and the consumer was registered.
*			false otherwise
*/
bool CustomDispatcher::subscribe(std::string producerId, Consumer* pConsumer) {

	if (!m_registeredProducers.contains(producerId)) {
		return false;
	}

	m_consumerProducerPairs[pConsumer].push_back(producerId);

	return true;
}

/*
* Main function of the dispatcher.
* 
* Calls the send() function of every producer and stores its message.
* It iterates over all registered consumers and notifies them for every registered producer,
* with the respective message.
*/
void CustomDispatcher::dispatchMessages() {
	std::unordered_map<std::string, std::string> receivedMessages;

	//Iterate over all registered producers
	for (auto producer = m_registeredProducers.begin(); producer != m_registeredProducers.end(); producer++) {
		//Receive message sent by producer
		receivedMessages[producer->first] = producer->second->send();
	}

	//Iterate over all registered consumers
	for (auto consumer = m_consumerProducerPairs.begin(); consumer != m_consumerProducerPairs.end(); consumer++) {
		//Iterate over all subscribed producers
		for (const std::string& producerID : consumer->second) {
			//Distribute messages from all producer, the consumer subscribed to
			consumer->first->notify(producerID, receivedMessages[producerID]);
		}
	}
}
