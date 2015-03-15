#include "FiniteStateMachine.h"
#include "TEMT6000.h"
#include "UltrasonicSensor.h"
#include "LimitSwitch.h"
#include "PinDefinitions.h"
#include "NineDOF.h"
#include "Wire.h"
#include "Motor.h"

#include "MsTimer2.h"

void start()
{
  // Do something like wait for nudge or button clicked
}

void calibrate()
{
  // Figure out where we might be relative to somewhere
}

void goToRamp()
{
  // based on calculated trajectory go towards ramp
}

void goUpRamp()
{
  // go up the ramp
}

void correctTraj()
{
  // correct ramp trajectory
}

void goDownRamp()
{
  // go down the ramp
}

void search()
{ 
  // search for the lego man
}

void goToLegoMan()
{
  // go to the lego man
}

void pickUp()
{
  // pick up the lego man
}

void goHome()
{
  // returning to home base
}

void chill()
{
  // chill at base
}

// Begin states
State Start = State(start);
State Calibrate = State(calibrate);
State GoToRamp = State(goToRamp);
State GoUpRamp = State(goUpRamp);
State CorrectTraj = State(correctTraj);
State GoDownRamp = State(goDownRamp);
State Search = State(search);
State GoToLegoMan = State(goToLegoMan);
State PickUp = State(pickUp);
State GoHome = State(goHome);
State Chill = State(chill);

FSM snr = FSM(Start); // search and rescue state machine
// End states

// Begin Sensors
UltrasonicSensor us_left = UltrasonicSensor(SONAR_TRIG_LEFT,SONAR_ECHO_LEFT);
UltrasonicSensor us_right = UltrasonicSensor(SONAR_TRIG_RIGHT,SONAR_ECHO_RIGHT);
UltrasonicSensor us_cen = UltrasonicSensor(SONAR_TRIG_CENTER,SONAR_ECHO_CENTER);

LimitSwitch ls_left = LimitSwitch(LIMIT_SWITCH_LEFT);
LimitSwitch ls_right = LimitSwitch(LIMIT_SWITCH_RIGHT);
LimitSwitch ls3_mid = LimitSwitch(LIMIT_SWITCH_MID);

// TEMT6000 reciever_left = TEMT6000(RECEIVER_LEFT);
// TEMT6000 reciever_right = TEMT6000(RECEIVER_RIGHT);

NineDOF ndof = NineDOF();
Motor mRight = Motor(MOTOR_LEFT_DIR_A,MOTOR_LEFT_DIR_B,MOTOR_LEFT_ENABLE);
Motor mLeft = Motor(MOTOR_RIGHT_DIR_A,MOTOR_RIGHT_DIR_B,MOTOR_RIGHT_ENABLE);

bool runMotors = false;

// End Sensors

// Begin calculations

bool calculateNav = false;

void doCalculations()
{
  calculateNav = false;
}

// End Calculations

void setup()
{
  Serial.begin (9600);
  Wire.begin();
  ndof.setup();

  attachInterrupt(4, thing, FALLING);
  MsTimer2::set(500, timerInterrupt);

  attachInterrupt(2, killSwitch, CHANGE);

  // We setup all our sensors up in this bitch.
}

void thing()
{
  runMotors = !runMotors;
}

void killSwitch()
{
  
}


void timerInterrupt()
{
    calculateNav = true;
}

void loop()
{
  /**
  * In this block we will transition from one state to another
  * For example we can switch from the start state to the calibrate state like so
  * snr.transitionTo(calibrate); 
  * then we update the state machine so it properly transitions
  * snr.update();
  */

  mLeft.setVelocity(255, 1);
  mRight.setVelocity(255, 1);

  Serial.print("Left Limit Switch: ");
  Serial.println(us_left.query());
  Serial.print("Right Limit Switch: ");
  Serial.println(us_right.query());
  Serial.print("Middle Limit Switch: ");
  Serial.println(us_cen.query());

  Serial.print("Left Ultrasonic: ");
  Serial.println(us_left.query());
  Serial.print("Right Ultrasonic: ");
  Serial.println(us_right.query());
  Serial.print("Center Ultrasonic: ");
  Serial.println(us_cen.query());
  Serial.println();

  // delay(100);

  //Serial.println(s2.query());
  if(calculateNav)
  {
    doCalculations();
  }
}

