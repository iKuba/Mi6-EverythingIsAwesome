/**
 * IRSensor.cpp
 */
#include "Arduino.h"
#include "IRSensor.h"

IRSensor::IRSensor(int inputPin) :
                                   input_pin_(inputPin)
{
  pinMode(input_pin_, INPUT);
}

int IRSensor::query()
{
	int value = analogRead(input_pin_);
	return value;
}