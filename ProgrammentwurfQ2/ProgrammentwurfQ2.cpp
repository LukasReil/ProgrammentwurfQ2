

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "TemperatureMonitor/TemperatureMonitor.h"
#include "apiWrapper/CustomDispatcher.h"
#include "Sensors/InsideTemperatureSensor.h"
#include "Sensors/OutsideTemperatureSensor.h"
#include "Sensors/SunIntensitySensor.h"
#include "Sensors/SensorMeasureThread.h"
#include "api/Umwelt.h"


int main()
{

	using namespace std::chrono_literals;

	Umwelt umwelt;
	CustomDispatcher customDispatcher(100ms);

	InsideTemperatureSensor insideTempSensor(0, &umwelt);
	OutsideTemperatureSensor outsideTempSensor(0, &umwelt);
	SunIntensitySensor sunIntensitySensor(0, &umwelt);

	customDispatcher.registerProducer(&insideTempSensor);
	customDispatcher.registerProducer(&outsideTempSensor);
	customDispatcher.registerProducer(&sunIntensitySensor);

	TemperatureMonitor tempMonitor(1000ms);
	tempMonitor.registerAtDispatcher(&customDispatcher);

	tempMonitor.startThread();	
	customDispatcher.startThread();
	SensorMeasureThread sensorMeasureThread(std::vector<Sensor*>{&insideTempSensor, &outsideTempSensor, &sunIntensitySensor}, 100ms);
	sensorMeasureThread.startThread();
	

	std::cin.get();
	
	tempMonitor.stopThread();
	sensorMeasureThread.stopThread();
	customDispatcher.stopThread();

	return 0;
}
