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
}

void Encoder::calculateSpeed()
{
  float dis = 0.00549778;
  curr_time_ = micros();
  delta_time_ = curr_time_ - prev_time_;
  prev_time_ = curr_time_;
  time_ = delta_time_/1000000;
    
  if (time_ != 0) 
  {
    speed = dis/time_;
  }
   else 
  {
    speed = 0;
  } 
}