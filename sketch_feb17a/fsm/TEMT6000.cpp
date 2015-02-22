/**
 * TEMT6000.cpp
 */
#include "Arduino.h"
#include "TEMT6000.h"

TEMT6000::TEMT6000(int temt6000pin) : temt6000pin_(temt6000pin)
{
  Serial.begin (9600); // I hope we can just set this as many times as we want
}

float TEMT6000::query()
{
  analogRead(temt6000Pin_);
}
