#pragma once

#include <string>

using namespace std;

class Consumer
{
    public:
        Consumer();

        // This function is called by the Dispatcher to notify the
        // Consumer about new messages from a subscribed Producer.
        // Implement this function to handle the new data.
        virtual void notify(string producerId, string msg) = 0;
};