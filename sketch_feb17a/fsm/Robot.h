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
#include "Accelerometer.h"
#include <Wire.h>
#include <Servo.h>

enum POSITION {CENTER, LEFT, RIGHT};

struct space {
  double x, y, z, heading;
};
class Robot
{
public:
  Robot();

  float getDistance(POSITION pos);

  uint8_t switches();
  void setup();
  void setVelocity(float vel);
  void setVelocity(float vel, POSITION pos);
  void rotate(float angle);
  void setBrush(bool brush);
  void propOn(bool on);
  void drive();
  bool haveLegoMan();
  bool checkForLegoMan();
  bool guardDown(POSITION pos);
  void killEverything();
  void reverse(int speed);
  space nav;

  static NineDOF ndof;

protected:

private:
	// Begin Sensors
  static UltrasonicSensor usRight, usCenter, usLeft;

	static LimitSwitch lsRight, lsCenter, lsLeft;

	static Servo prop_;

  static Accelerometer accLeft, accRight;
	// End Sensors

	// motors
	static Motor mLeft, mRight, mBrush;

	float velocityLeft_, velocityRight_;
	bool brush_, legoMan_;

	// end motors
};

#endif
