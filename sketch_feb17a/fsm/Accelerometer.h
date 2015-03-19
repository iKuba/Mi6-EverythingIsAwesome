/*
* Accelerometer.h
*/

#ifndef Accelerometer_h
#define Accelerometer_h

#include "Arduino.h"
class Accelerometer
{

public:
  /**
   * Constructor for the limit switch
   */
   Accelerometer(int inputPin);
   Accelerometer(){};
  /*
   *  Returns position of the accelerometer
   */
   int getPosition();

private:
	int input_pin_;
};

#endif