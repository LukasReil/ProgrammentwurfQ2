#include "MyDispatcher.h"


int main()
{
    /*
    Create all Sensors, Controllers and Actuators
    */

    // Create new Dispatcher
    MyDispatcher dispatcher;

    // Register all Producers
    dispatcher.registerProducer(&sensor1);
    dispatcher.registerProducer(&sensor2);
    dispatcher.registerProducer(&controller1);

    // Subscribe Consumers
    dispatcher.subscribe(IDSensor1, &consumer1);
    dispatcher.subscribe(IDSensor2, &consumer2);
    dispatcher.subscribe(IDSensor2, &controller1);
    dispatcher.subscribe(IDSensor2, &actuator1);

    // Start Dispatcher
    dispatcher.run();
}