/**
 * Encoder.cpp
 */
#include "Arduino.h"
#include "Encoder.h"

Encoder::Encoder(int pinA, int pinB) :
                                   pinA_(pinA), pinB_(pinB)
{
  pinMode(pinA_, INPUT);
  pinMode(pinB_, INPUT);
  digitalWrite(pinA_, HIGH); //turn pullup resistor on
  digitalWrite(pinB_, HIGH); //turn pullup resistor on
  curr_time_ = micros();
}

void Encoder::calculateSpeed()
{
  double dis = 0.00549778;
  curr_time_ = micros();

  if (count%4 == 0)
  {
    delta_time_ = curr_time_ - prev_time_;
    prev_time_ = curr_time_;
    time_ = delta_time_/1000000;
      
    if (time_ != 0) 
    {
      speed = dis/time_;
    }
     else 
    {
      speed = 6;
    } 

  }

}