

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "api/Umwelt.h"

#include "apiWrapper/CustomDispatcher.h"
#include "Sensors/InsideTemperatureSensor.h"
#include "Sensors/OutsideTemperatureSensor.h"
#include "Sensors/SunIntensitySensor.h"
#include "Sensors/SensorMeasureThread.h"
#include "TemperatureMonitor/TemperatureMonitor.h"
#include "actors/JalousieSteuerung.h"
#include "controllers/JalousieController.h"


int main()
{

	using namespace std::chrono_literals;

	Umwelt umwelt;
	CustomDispatcher customDispatcher(50ms);

	InsideTemperatureSensor insideTempSensor(0, &umwelt);
	OutsideTemperatureSensor outsideTempSensor(0, &umwelt);
	SunIntensitySensor sunIntensitySensor(0, &umwelt);

	JalousieController jalousieController1(0);
	TemperatureMonitor tempMonitor(50ms);
	JalousieSteuerung jalousieSteuerung1(0, 0, 50ms);

	//Register Producers
	customDispatcher.registerProducer(&insideTempSensor);
	customDispatcher.registerProducer(&outsideTempSensor);
	customDispatcher.registerProducer(&sunIntensitySensor);
	customDispatcher.registerProducer(&jalousieSteuerung1);

	//Register Controllers
	try {
		jalousieController1.registerAtDispatcher(&customDispatcher);

		//Register Consumers
		tempMonitor.registerAtDispatcher(&customDispatcher);
		jalousieSteuerung1.registerAtDispatcher(&customDispatcher);
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		return -1;
	}


	tempMonitor.startThread();	
	customDispatcher.startThread();
	SensorMeasureThread sensorMeasureThread(std::vector<Sensor*>{&insideTempSensor, &outsideTempSensor, &sunIntensitySensor, &jalousieSteuerung1}, 100ms);
	sensorMeasureThread.startThread();
	//jalousieController1.startThread();
	jalousieSteuerung1.startThread();
	

	std::cin.get();
	
	tempMonitor.stopThread();
	sensorMeasureThread.stopThread();
	customDispatcher.stopThread();
	//jalousieController1.stopThread();
	jalousieSteuerung1.stopThread();

	return 0;
}
