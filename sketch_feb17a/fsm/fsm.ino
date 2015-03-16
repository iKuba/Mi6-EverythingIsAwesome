#include "FiniteStateMachine.h"
#include "PinDefinitions.h"
#include "Wire.h"
#include "MsTimer2.h"
#include <Servo.h>
#include "Robot.h"

#define START digitalRead(START_BUTTON)

Robot r;

void idle()
{
  // Do something like wait for nudge or button clicked
  // Wait for button push #define START_BUTTON 24
  // if(START_BUTTON == pressed)
  // turn robot on i.e exit this condition and proceed
}

void calibrate()
{
  while(r.getDistance(LEFT) != r.getDistance(RIGHT))
  {
     if(r.getDistance(LEFT)>r.getDistance(RIGHT))
       r.rotate(.5);
     else
       r.rotate(-.5);
  }
}

void goToRamp()
{
  if(!r.haveLegoMan())
  {
    r.rotate(90.0);
    // This means we are on the platform
    while(r.ndof.gyro_.y == 0)
      r.setVelocity(.5);
    // This means we are rolling down the ramp we should have a slow change in pitch
    while(r.ndof.gyro_.y != 0)
      r.setVelocity(.5);
    calibrate();
    while(r.getDistance(CENTER) > 5);
      r.setVelocity(.5);
    r.rotate(-90.0);
    while(r.ndof.gyro_.y == 0)
      r.setVelocity(.5);
    // drive forward until the ramp is engaged (we will again see a change in yaw)
  }
}

void goUpRamp()
{
  while (!r.guardDown(LEFT) || !r.guardDown(RIGHT))
  {
    if (!r.guardDown(LEFT))
    {
      r.setVelocity(.5, RIGHT);
    }
    else
    {
      r.setVelocity(.5, LEFT);
    }
  }
  r.ndof.refresh();
  while (r.ndof.gyro_.y > 10)
  {
    r.ndof.refresh();
    r.setVelocity(.5);
  }
  r.propOn(true);
  while(r.ndof.gyro_.y < 10)
    r.drive();
  r.propOn(false);
  r.setVelocity(0);
}

void correctTraj()
{
  // correct ramp trajectory
}

void goDownRamp()
{
  while(r.ndof.gyro_.y > -10)
  {
    r.setVelocity(.1);
  }
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
State Idle = State(idle);
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

FSM snr = FSM(Idle); // search and rescue state machine
// End states

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
  MsTimer2::set(500, timerInterrupt);
  attachInterrupt(2, killSwitch, CHANGE);
  r = Robot();
  r.setup();

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
  * 
  */
  //Serial.println(s2.query());
  if (START)
  {
    snr.transitionTo(Calibrate);
  }
  else if(r.getDistance(LEFT) != r.getDistance(RIGHT))
  {
    snr.transitionTo(GoToRamp);
  }
  if(calculateNav)
  {
    doCalculations();
  }
  snr.update();
}

