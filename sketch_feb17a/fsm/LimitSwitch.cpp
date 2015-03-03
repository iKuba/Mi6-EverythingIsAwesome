/**
 * LimitSwitch.cpp
 */
#include "Arduino.h"
#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(int inputPin) :
                                   input_pin_(inputPin)
{
  pinMode(input_pin_, INPUT);
}

bool LimitSwitch::query()
{
  return digitalRead(input_pin_);
}