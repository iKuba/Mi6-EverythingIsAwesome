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

int Accelerometer::getPosition()
{
	return analogRead(input_pin_)-505;
}