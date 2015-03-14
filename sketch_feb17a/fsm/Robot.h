/**
 * Look at me I'm a header file
 *
 * robot.h
 */
#ifndef Robot_h
#define Robot_h

#include "Arduino.h"
#include "UltrasonicSensor.h"
#include "PinDefinitions.h"
#include "LimitSwitch.h"
#include "NineDOF.h"
#include <Wire.h>

class Robot
{
public:
  enum POSITION {CENTER, LEFT, RIGHT};
  Robot();

  float getDistance(POSITION pos);

  uint8_t switches();
  void setup();

protected:

private:
	// Begin Sensors
	static UltrasonicSensor usRight;
	static UltrasonicSensor usBack;
	static UltrasonicSensor usLeft;

	static LimitSwitch lsRight;
	static LimitSwitch lsCenter;
	static LimitSwitch lsLeft;

	static NineDOF ndof;
	// End Sensors
};

#endif
