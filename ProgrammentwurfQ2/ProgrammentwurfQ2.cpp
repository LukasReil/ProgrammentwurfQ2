

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
#include "actors/Jalousie.h"
#include "controllers/JalousieController.h"
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

	JalousieController jalousieController1(0);
	jalousieController1.registerAtDispatcher(&customDispatcher);
	customDispatcher.registerProducer(&jalousieController1);

	Jalousie jalousie1(0, 500ms);
	jalousie1.registerAtDispatcher(&customDispatcher);


	tempMonitor.startThread();	
	customDispatcher.startThread();
	SensorMeasureThread sensorMeasureThread(std::vector<Sensor*>{&insideTempSensor, &outsideTempSensor, &sunIntensitySensor}, 100ms);
	sensorMeasureThread.startThread();
	jalousie1.startThread();
	

	std::cin.get();
	
	tempMonitor.stopThread();
	sensorMeasureThread.stopThread();
	customDispatcher.stopThread();
	jalousie1.stopThread();

	return 0;
}
