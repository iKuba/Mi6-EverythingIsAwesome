/**
 * Look at me I'm a header file
 *
 * UltrasonicSensor.h
 */
#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

#include "Arduino.h"
class UltrasonicSensor
{
public:
  /**
   * Constructor for the ultrasonic sensor
   */
  UltrasonicSensor(int triggerPin, int echoPin);
  UltrasonicSensor(){};

  /**
   * Asking ultrasonic for distance returns a distance float in cm
   */
  float query();

private:
  int trigger_pin_;
  int echo_pin_;
};

#endif
