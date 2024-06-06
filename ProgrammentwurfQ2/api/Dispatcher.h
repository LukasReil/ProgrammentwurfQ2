#pragma once

#include <string>
#include <map>
#include <vector>

#include "Producer.h"
#include "Consumer.h"

using namespace std;

class Dispatcher
{    
    public:
        Dispatcher();

        // Register a Producer. The unique ID of the producer is contained
        // in the Producer
        virtual bool registerProducer(Producer* pProducer) = 0;

        // Subscribe the passed Consumer to messages of the Producer with the
        // passed producerId
        virtual bool subscribe(string producerId, Consumer* pConsumer) = 0;

        // Starts the dispatcher. Make sure that all Producers are registered
        // and all Consumers have subscribed befor starting the Dispatcher
        void run();

        // Handles the dispatching of the messages between all registered Consumers
        // ans the subscribing Producers. This means that this function must call
        // for each Producer the method send() and collect the message from the 
        // Producer. Then it must check which Consumers have subscribed to the
        // Producer and call the notify(...) method of each Consumer that subscribed
        // to the Producer.
        virtual void dispatchMessages() = 0;
};