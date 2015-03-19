/*
* LimitSwitch.h
*/

#ifndef LimitSwitch_h
#define LimitSwitch_h

#include "Arduino.h"
class LimitSwitch
{

public:
  /**
   * Constructor for the limit switch
   */
   LimitSwitch(int inputPin);
   LimitSwitch(){};

  /**
   * Checking if the limit switch has been hit, returns true or false
   */
   bool query();

private:
	int input_pin_;
};

#endif