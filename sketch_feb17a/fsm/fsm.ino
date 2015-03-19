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
  // turn robot on i.e exit this co ndition and proceed
  // wait on spark io.
}

void calibrate()
{
  // We only want cm accuracy
  while((int)r.getDistance(LEFT) != (int)r.getDistance(RIGHT))
  {
     if(r.getDistance(LEFT)>r.getDistance(RIGHT))
       r.rotate(1.0);
     else
       r.rotate(-1.0);
  }
  r.ndof.refresh();

  // This function will be called in multiple states; we must figure out a 
  // way to decouple the r.nax.x setting such that we can fix x and y

  // for now we'll use center, since we don't know the offset of our ultrasonics
  r.nav.x = r.getDistance(CENTER);
  // just need this here for reasons while I wait on ndof heading code
  r.nav.heading = r.ndof.heading();
}
/**
* Lots of tuning required
*/
void goToRamp()
{
  if(!r.haveLegoMan())
  {
    // Chris - try to remove the nave by just rotating and finding the far wall
    // then align with the ramp as we move forward.  The ramp will never change
    // place
    // also this needs a if lego man check to do it if we are on the other side of the wall.
    r.rotate(90.0);
    // This means we are on the platform
    r.nav.heading = r.ndof.heading();
    while(r.ndof.gyro_.y == 0)
      r.setVelocity(.5);
    // This means we are rolling down the platform we should have a slow change in pitch
    while(r.ndof.gyro_.y != 0)
      r.setVelocity(.5);

    // this really should be a call to calibrate BUT we need to get rid of
    // the fixing the x in it.
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

// need to do velocity tuning for moving us into position
// also need to figure out if we need the props down
// we also need to do roll detection to turn off the prop if something fucks up
// This state exits when we are at the peak and detect a pitch or we fuck up
// The next state engaged will be the go down ramp
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
  // need to determine threshholds on gyro
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

  //leaving by gyro sensor/acceleronmeter change
}

void correctTraj()
{
  // no longer needed
}

// need to find gyro threshold
// This state is disengaged once we are off the ramp.
// We will either go home or find the lego man, pending whether we already
// have the lego man
void goDownRamp()
{
  while(r.ndof.gyro_.y > -10)
    r.setVelocity(.2);
}

// Jakub will work on search
//debate between using a pre made model and scanning each time new
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

// We need to figure out how we deal with this state
// this will be the state that happens after we detect the lego man.
// we might have a heading or somehting like that. I don't know yet.
// This state is engaged once we have found the base of the lego man
void goToLegoMan()
{
  r.setVelocity(.3);
  r.setBrush(true);
  // spin brush until we have the lego man
  //leave this state based on the gyro/acceleronmeter hitting the base
  //this is a debatable state and would almost combine it with the "Pickup state"
}

// We should be going across the platform here
// This state is engaged once we have detected we are at the lego man's base
void pickUp()
{
  // pick up the lego man
  //leave when limit switch is triggered
}

// This probably needs tuning, we might be able to scan for it we might be 
// able to hardcode it, hardcoding is probably the best option for now
// because we have a lot of wiggle room to deal with it since the 
// platform is huge
void goHome()
{
  int t = millis();
  while (millis() < t + 1000)
  {
    r.setVelocity(.1);
  }
  r.rotate(90);
  t = millis();
  while (millis() < t + 1000)
  {
    r.setVelocity(.3);
  }
  //needs a lot of work, I could see this being the mirror of the search state
  // as we've just gotten off the ramp and need to go toward a base
}

// Literally chill.
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

void doCalculations(){
  calculateNav = false;
}

// End Calculations

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  MsTimer2::set(500, timerInterrupt);
  attachInterrupt(0, killSwitch, CHANGE);
  r = Robot();
  r.setup();

  // We setup all our sensors up in this bitch.
}

// need proper implementation
void killSwitch()
{
  
}

// not necessary anymore
void timerInterrupt()
{
  calculateNav = true;
}


// Need to write the transitions between states and shit
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
  // if (START)
  // {
  //   snr.transitionTo(Calibrate);
  // }
  // else if(r.getDistance(LEFT) != r.getDistance(RIGHT))
  // {
  //   snr.transitionTo(GoToRamp);
  // }
  // if(calculateNav)
  // {
  //   doCalculations();
  // }
  // snr.update();

  // Serial.println(r.ndof.heading());
  // for (int x = 0; x < 180; x ++)
  // {
  //   Serial.println("Going into rotate");
  //   r.rotate(1.0);
  //   Serial.println("Hai");
  //   delay(10);
  //   Serial.println(String((int) r.getDistance(LEFT)) + " " + String((int) r.getDistance(RIGHT)));
  // }
  r.setVelocity(.3);
}

