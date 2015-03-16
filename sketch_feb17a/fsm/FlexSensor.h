/*
* FlexSensor.h
*/

#ifndef FlexSensor_h
#define FlexSensor_h

#include "Arduino.h"
class FlexSensor
{

public:
  /**
   * Constructor for the flex sensor
   */
   FlexSensor(int inputPin);

  /**
   * Check if the Lego man is in the sled.
   */
   int query();

private:
	int input_pin_;
};

#endif