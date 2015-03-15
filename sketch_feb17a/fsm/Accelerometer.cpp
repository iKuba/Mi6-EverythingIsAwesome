/**
 * Accelerometer.cpp
 */
#include "Arduino.h"
#include "Accelerometer.h"

Accelerometer::Accelerometer(int inputPin) :
                                   input_pin_(inputPin)
{
  pinMode(input_pin_, INPUT);
}

bool Accelerometer::getPosition()
{
	delay(10);
	position = analogRead(input_pin_);
	position = data-505;
	return position;
}