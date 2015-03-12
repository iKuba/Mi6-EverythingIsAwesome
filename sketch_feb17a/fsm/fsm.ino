#include "FiniteStateMachine.h"
#include "TEMT6000.h"
#include "UltrasonicSensor.h"
#include "LimitSwitch.h"
#include "PinDefinitions.h"
#include "NineDOF.h"
#include "Wire.h"
#include "MsTimer2.h"

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
      //Check Accelerametor on guides to see if guides are down
        //if not turn robot until both guide accelerameter indicate it is vertical
        //if it is procedd witj turning prop on and ramping of prop speed
        // once speed reached proceed with climbing of ramp
          //check if guides are moving up 
          // if it is left
            // turn left slightly util it is no longer up
            //should see what kind of correction is needed to be straight on the ramp
          // if it is right 
            // turn right slightly until it is no longer up
            //should see what kind of correction is needed to be straight on the ramp
          // if not procceed forward
}

void correctTraj()
{
  // correct ramp trajectory
}

void goDownRamp()
{
  //this state will happen realy fast since we are sliding down ramp fast
  // go down the ramp
  //Check 9DOF to check angle
    //if not keep moving forward until correct angle
    //if yes
    //drive in reverse and stop prop immediately
    // option to check guide accelerameter to ensure still on ramp.
}

void search()
{ 
  // search for the lego man
  // drive arround in determined path via path planning using ultrasonics
  // use ultrasound and encoders to track where we are
  // once path have been determined check limit switchs to see if hit base
  // limit siwthc adjsut logic

    //if all three hit flush with base 
    // climb base mobe to next state

    //if left limit hit car need to turn to the right until all three hit
    // could be 3 possible situations
      // 1 - car is aligned to base but only the left side 
      // 1 - and care need to shift to the left
      // 2 - car is not aligned and at a angle such that the left side of the car is on base and right is not
      // 2 - we can check 9dof sensor to see orientation and adjust by turn left (Different from shifting right)
      // 2 - until all three limit is triggered and car is angled
      // 3 - if only left and right hit we are at corner then back off move to one direction and try again
      // 3 - then back off a certain distance
      // 3 - turn right or left 45 degrees
      // 3 - move forward a known distance
      // 3 - turn 90 degrees the opposite of what did previously
      // 3 - move forward to see if all three limit will trigger and repeat.

    //in right limit hit car need to turn to the left until all three hit
      // same with only left

    // if left and center or right and center hit
      // if left and center car need to be shifted to the left/
        // plan path via back off a certain known distance
        // turn 90 degree left
        // move a certain known distance
        // turn right 90 degree right
        // try again

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
UltrasonicSensor us1 = UltrasonicSensor(SONAR_TRIG1,SONAR_ECHO1);
UltrasonicSensor us2 = UltrasonicSensor(SONAR_TRIG2,SONAR_ECHO2);
UltrasonicSensor us3 = UltrasonicSensor(SONAR_TRIG3,SONAR_ECHO3);

LimitSwitch ls1 = LimitSwitch(LIMIT_SWITCH_1);
LimitSwitch ls2 = LimitSwitch(LIMIT_SWITCH_2);
LimitSwitch ls3 = LimitSwitch(LIMIT_SWITCH_3);

TEMT6000 reciever_left = TEMT6000(RECEIVER_LEFT);
TEMT6000 reciever_right = TEMT6000(RECEIVER_RIGHT);

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
}

