/**
 * UltrasonicSensor.cpp
 */
#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) :
                                   trigger_pin_(triggerPin), echo_pin_(echoPin)
{
  pinMode(trigger_pin_, OUTPUT);
  pinMode(echo_pin_, INPUT);
}

float UltrasonicSensor::query()
{
  int duration, distance;
  digitalWrite(trigger_pin_, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigger_pin_, LOW);
  duration = pulseIn(echo_pin_, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 400 || distance <= 0)
  {
    return -1.0;
  }
  else
  {
    return distance;
  }
}
