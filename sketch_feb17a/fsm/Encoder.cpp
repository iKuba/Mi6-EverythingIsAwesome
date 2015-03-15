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

void Encoder::calculateSpeed(double curr_time, double prev_time, double delta_time, double time, double &speed) :
							curr_time_(curr_time), prev_time_(prev_time), delta_time_(delta_time), time_(time), &speed_(speed)
{
  	curr_time_ = micros();
  	delta_time_ = curr_time_ - prev_time_;
    prev_time_ = curr_time_;
    time_ = delta_time_/1000000;
    
    if (time_ != 0) 
    {
      speed_ = dis/t;
    }
    else 
    {
      speed_ = 0;
    }
  } 
    return speed_;
  }
}