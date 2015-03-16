/**
 * LimitSwitch.cpp
 */
#include "Arduino.h"
#include "FlexSensor.h"

FlexSensor::FlexSensor(int inputPin) :
                                   input_pin_(inputPin)
{
  pinMode(input_pin_, INPUT);
}

int FlexSensor::query()
{
	int flexSensorReading = analogRead(input_pin_);

	//In my tests I was getting a reading on the arduino between 782, and 920. 
	//Using map(), I converted those values to a 0-100 range
	int flex0to100 = map(flexSensorReading, 782, 920, 0, 100);

	// if (flex0to100 > 10) {
	// 	return 1;
	// }
	// else {
	// 	return 0;
	// }
	return flexSensorReading;
}