/**
 * Look at me I'm a header file
 *
 * Robot.h
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
#include <Servo.h>

class Robot
{
public:
  Robot();
  enum POSITION {CENTER, LEFT, RIGHT};

  float getDistance(POSITION pos);

  uint8_t switches();
  void setup();
  void setVelocity(float vel);
  void setVelocity(float vel, POSITION pos);
  void rotate(float angle);
  void setBrush(bool brush);
  void propOn(bool on);
  void drive();

protected:

private:
	// Begin Sensors
  static UltrasonicSensor usRight, usCenter, usLeft;

	static LimitSwitch lsRight, lsCenter, lsLeft;

  static NineDOF ndof;

	static Servo prop_;
	// End Sensors

	// motors
	static Motor mLeft, mRight, mBrush;

	float velocityLeft_, velocityRight_;
	int propSpeed_;
	bool brush_;

	// end motors
};

#endif
