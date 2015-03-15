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
#include "Motor.h"
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
	static UltrasonicSensor usRight, usCenter, usLeft;

	static LimitSwitch lsRight, lsCenter, lsLeft;

	static NineDOF ndof;
	// End Sensors

	// motors

	static Motor mLeft, mRight, mBrush;

	// end motors
};

#endif
