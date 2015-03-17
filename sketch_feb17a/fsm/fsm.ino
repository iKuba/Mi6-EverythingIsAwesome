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
  r.ndof.refresh();
  // for now we'll use center, since we don't know the offset of our ultrasonics
  r.nav.x = r.getDistance(CENTER);
  // just need this here for reasons while I wait on ndof heading code
  r.nav.heading = 0;
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
    while(r.getDistance(LEFT) != r.getDistance(RIGHT))
    {
       if(r.getDistance(LEFT)>r.getDistance(RIGHT))
         r.rotate(.5);
       else
         r.rotate(-.5);
    }
    r.nav.y = r.getDistance(CENTER) + 150;
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
  // no longer needed
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
  int t = millis();
  int dPrevL, dPrevR;
  // We first move 10 cm from the ramp.
  while (millis() < t + 1000)
    r.setVelocity(.1);
  
  dPrevL = r.getDistance(LEFT);
  dPrevR = r.getDistance(RIGHT);
  for (int x = 1; x < 180; x++)
  {
    r.rotate(-1);
    if (abs(r.getDistance(LEFT) - dPrevL) > 20)
    {
      while(abs(r.getDistance(RIGHT) - dPrevR) < 20)
        r.rotate(-1);
      // now drive, maybe?
    }
    if (abs(r.getDistance(RIGHT) - dPrevR) > 20)
    {
      // rotate back to try and find the base with the other ultra sonic,
      // rotate half way back. DRIVE
    }
    dPrevL = r.getDistance(LEFT);
    dPrevR = r.getDistance(RIGHT);
  }
}

void goToLegoMan()
{
  r.setVelocity(.3);
  r.setBrush(true);
  // spin brush until we have the lego man
}

void pickUp()
{
  // pick up the lego man
}

void goHome()
{
  int t = millis();
  while (millis() < t + 1000)
  {
    m.setVelocity(.1);
  }
  r.rotate(90);
  t = millis();
  while (millis() < t + 1000)
  {
    m.setVelocity(.3);
  }
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

