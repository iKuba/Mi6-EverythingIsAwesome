/**
 * Motor.cpp
 */
#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int forwardPin, int reversePin, int enablePin) : 
                                   forward_pin_(forwardPin), 
                                   reverse_pin_(reversePin),
                                     enable_pin_(enablePin)
{
  pinMode(forward_pin_, OUTPUT);
  pinMode(reverse_pin_, OUTPUT);
  pinMode(enable_pin_, OUTPUT);
 
  //digitalWrite(enable_pin_, HIGH);
}

Motor::Motor(int enablePin) : enable_pin_(enablePin)
{
  pinMode(enable_pin_, OUTPUT);
 
  //digitalWrite(enable_pin_, HIGH);
}

void Motor::setVelocity(unsigned int speed, bool direction, bool brushFlag)
{ 
  analogWrite(enable_pin_, speed);
  if(direction)
  {
    digitalWrite(forward_pin_, HIGH);
    digitalWrite(reverse_pin_, LOW);
  }
  else
  {
    digitalWrite(forward_pin_, LOW);
    digitalWrite(reverse_pin_, HIGH);
  }
}

void Motor::setVelocity(unsigned int speed)
{
  analogWrite(enable_pin_, speed);
}
