#include "Dispatcher.h"

#include <thread>

Dispatcher::Dispatcher()
{
}

void Dispatcher::run()
{
    while(true)
    {
        // Does the magic
        dispatchMessages();

        // Lets Dispatcher sleep for a second
        this_thread::sleep_for(chrono::seconds(1));
    }
}
