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
  Motor(int brushmotorPin, int brushSpeed);
  void setVelocity(unsigned int speed, bool direction);


private:
  int forward_pin_, reverse_pin_, enable_pin_, brushmotor_pin_, brushSpeed_pin_;
};

#endif
