#include "FiniteStateMachine.h"
#include "TEMT6000.h"
#include "UltrasonicSensor.h"
#include "LimitSwitch.h"
#include "PinDefinitions.h"
#include "NineDOF.h"
#include "Wire.h"
<<<<<<< HEAD
#include "Motor.h"

=======
#include "MsTimer2.h"
>>>>>>> 56ae2b9d685711a18e18a1b88a7e2c8a90248dfd

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
<<<<<<< HEAD
UltrasonicSensor us1 = UltrasonicSensor(40,A12); //Back
// UltrasonicSensor us2 = UltrasonicSensor(,); //Left
UltrasonicSensor us3 = UltrasonicSensor(44,A2); //Right
=======
// End states

// Begin Sensors
UltrasonicSensor us1 = UltrasonicSensor(SONAR_TRIG1,SONAR_ECHO1);
UltrasonicSensor us2 = UltrasonicSensor(SONAR_TRIG2,SONAR_ECHO2);
UltrasonicSensor us3 = UltrasonicSensor(SONAR_TRIG3,SONAR_ECHO3);
>>>>>>> 56ae2b9d685711a18e18a1b88a7e2c8a90248dfd

LimitSwitch ls1 = LimitSwitch(LIMIT_SWITCH_1);
LimitSwitch ls2 = LimitSwitch(LIMIT_SWITCH_2);
LimitSwitch ls3 = LimitSwitch(LIMIT_SWITCH_3);

LimitSwitch testSwitch = LimitSwitch(42);

TEMT6000 reciever_left = TEMT6000(RECEIVER_LEFT);
TEMT6000 reciever_right = TEMT6000(RECEIVER_RIGHT);

NineDOF ndof = NineDOF();
Motor mLeft = Motor(3,4,2);
Motor mRight = Motor(5,6,7);

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
<<<<<<< HEAD
  attachInterrupt(4, thing, FALLING);
=======
  MsTimer2::set(500, timerInterrupt);

  attachInterrupt(2, killSwitch, CHANGE);
>>>>>>> 56ae2b9d685711a18e18a1b88a7e2c8a90248dfd

  // We setup all our sensors up in this bitch.
}

<<<<<<< HEAD
void thing()
{
  runMotors = !runMotors;
=======
void killSwitch()
{
  
}


void timerInterrupt()
{
    calculateNav = true;
>>>>>>> 56ae2b9d685711a18e18a1b88a7e2c8a90248dfd
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
<<<<<<< HEAD

  // Serial.println(runMotors);
  // if (runMotors)
  // {
  //   mLeft.setVelocity(255, 1);
  //   mRight.setVelocity(255, 1);
  // }
  // Serial.println(s2.query());

  Serial.print("Left Ultrasonic: ");
  Serial.println(us3.query());
  Serial.println();

  // Serial.print("Back Ultrasonic: ");
  // Serial.println(us1.query());
  // Serial.println();

  // Serial.print("Right Ultrasonic: ");
  // Serial.println(us3.query());
  // Serial.println();

  // delay(100);
=======
  //Serial.println(s2.query());
  if(calculateNav)
  {
    doCalculations();
  }
>>>>>>> 56ae2b9d685711a18e18a1b88a7e2c8a90248dfd
}

