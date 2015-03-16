/*
* IRSensor.h
*/

#ifndef IRSensor_h
#define IRSensor_h

#include "Arduino.h"
class IRSensor
{

public:
  /**
   * Constructor for the flex sensor
   */
   IRSensor(int inputPin);

  /**
   * Check if the Lego man is in the sled.
   */
   int query();

private:
	int input_pin_;
};

#endif