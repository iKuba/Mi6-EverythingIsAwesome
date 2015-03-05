/**
 * Look at me I'm a header file
 *
 * Motor.h
 */
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
class Motor
{
public:
  /**
   * Constructor for the light intensity sensor
   */
  Motor(int forwardPin, int reversePin, int enablePin);
  Motor(int enablePin);
  void setVelocity(unsigned int speed, bool direction, bool brushFlag);


private:
  int forward_pin_, reverse_pin_, enable_pin_;
};

#endif
