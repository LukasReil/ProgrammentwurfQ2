#pragma once

#include <string>

using namespace std;

class Producer
{
        string id;

    public:

        // Pass a unique id, that clearly identifies the Producer,
        // to the Constructor
        Producer(string id);

        // This funktion is called by the Dispatcher to ask the Producer for
        // new data. Implement this function to return a string that contains
        // the message that the Producer wants to send. The dispatcher will for-
        // ward the message to all Consumers that subscribed to this Producer.
        // If you send an empty string ("") the Dispatcher will ignore the message
        // and not forward it the the subscribed Consumers
        virtual string send() = 0;

        // Returns the unique ID of the Producer
        string getId();
};