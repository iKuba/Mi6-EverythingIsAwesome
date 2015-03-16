#include "FiniteStateMachine.h"
#include "TEMT6000.h"
#include "UltrasonicSensor.h"
#include "LimitSwitch.h"
#include "PinDefinitions.h"
#include "NineDOF.h"
#include "Wire.h"
#include "MsTimer2.h"
#include "IRSensor.h"

void start()
{
  // Do something like wait for nudge or button clicked
  // Wait for button push #define START_BUTTON 24
  // if(START_BUTTON == pressed)
  // turn robot on i.e exit this condition and proceed
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
  //Check 9DOF to check angle
    //if not back away and re enter ramp
    //if yes
      //Check Accelerametor to see if guides are down
        //if not turn robot until both guide accelerameter indicate it is vertical
        //if it is procedd witj turning prop on and ramping of prop speed
        // once speed reached proceed with climbing of ramp
}

void correctTraj()
{
  // correct ramp trajectory
}

void goDownRamp()
{
  // go down the ramp
  //Check 9DOF to check angle
    //if not keep moving forward until correct angle
    //if yes
    //stop driving and stop prop
    // option to check guide accelerameter to ensure still on ramp.
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
// UltrasonicSensor us1 = UltrasonicSensor(SONAR_TRIG1,SONAR_ECHO1);
// UltrasonicSensor us2 = UltrasonicSensor(SONAR_TRIG2,SONAR_ECHO2);
// UltrasonicSensor us3 = UltrasonicSensor(SONAR_TRIG3,SONAR_ECHO3);

// LimitSwitch ls1 = LimitSwitch(LIMIT_SWITCH_1);
// LimitSwitch ls2 = LimitSwitch(LIMIT_SWITCH_2);
// LimitSwitch ls3 = LimitSwitch(LIMIT_SWITCH_3);

// TEMT6000 reciever_left = TEMT6000(RECEIVER_LEFT);
// TEMT6000 reciever_right = TEMT6000(RECEIVER_RIGHT);

IRSensor ir = IRSensor(IR_SIGNAL);

NineDOF ndof = NineDOF();

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
  MsTimer2::set(500, timerInterrupt);

  attachInterrupt(2, killSwitch, CHANGE);

  // We setup all our sensors up in this bitch.
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
  //Serial.println(s2.query());
  if(calculateNav)
  {
    doCalculations();
  }
  Serial.print("Value: ");
  Serial.println(ir.query());
  Serial.println();

  delay(500);

}

