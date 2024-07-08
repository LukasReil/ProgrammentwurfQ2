#include "JalousieController.h"

const std::string JalousieController::sunIntensitySensorID{ "SunIntensitySensor0" };
const std::string JalousieController::insideTemperatureSensorID{ "InsideTemperatureSensor0" };
const std::string JalousieController::jalousieSensorID{ "JalousieSensor0" };

JalousieController::JalousieController(int jalousieControllerID)
	:	Controller::Controller("JalousieController" + std::to_string(jalousieControllerID), 
		std::vector<std::string>{sunIntensitySensorID, insideTemperatureSensorID, jalousieSensorID}) {}

/*
* Depending on the message sender, the jalousie controller sets either its sun intensity,
* inside temperature or measured jalousie status member variables. 
* Depending on these it sends the appropriate command to the Jalousie.
* 
* @param producerID: ID of the producer that sends a message
* @param msg: The sent message
*/
void JalousieController::notify(std::string producerID, std::string msg) {

	double msgDouble = strtod(msg.c_str(), nullptr);

	if (producerID == sunIntensitySensorID) {
		std::string o = "Sun Intensity is at " + msg + "% \n";
		//std::cout << o;
		m_sunIntensity = msgDouble;
	} else if (producerID == insideTemperatureSensorID) {
		m_insideTemperature = msgDouble;
	} else if (producerID == jalousieSensorID) {
		m_measuredJalousieStatus = msgDouble;
	}

	if (m_insideTemperature > 22.0 && m_sunIntensity > 20.0) {
		m_calculatedJalousieStatus = 0.90;
	} else if (m_insideTemperature > 20.0 && m_sunIntensity > 50.0) {
		m_calculatedJalousieStatus = 0.70;
	} else {
		m_calculatedJalousieStatus = 0.0;
	}
}

/*
* Sends out the calculated jalousie status.
* 
* @return the calculated jalousie status as a string.
*/
std::string JalousieController::send() {
	return std::to_string(m_calculatedJalousieStatus);
}
