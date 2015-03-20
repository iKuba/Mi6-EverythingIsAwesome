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
  float lDist = 0;
  float rDist = 99;

  while(abs(lDist - rDist) > .5)
  {
    lDist = r.getDistance(LEFT);
    delay(200);
    rDist = r.getDistance(RIGHT);
    if(lDist == -1 || rDist == -1)
      continue;
    Serial.println(abs(lDist - rDist));
     if(lDist>rDist)
     {  
      r.rotate(1.0);
     }
     else
     {
       r.rotate(-1.0);
     }
    Serial.println(lDist);
    Serial.println(rDist);
  }
  Serial.println(lDist);
    Serial.println(rDist);
  r.ndof.refresh();

  // This function will be called in multiple states; we must figure out a 
  // way to decouple the r.nax.x setting such that we can fix x and y

  // for now we'll use center, since we don't know the offset of our ultrasonics
  r.nav.x = r.getDistance(CENTER);
  // just need this here for reasons while I wait on ndof heading code
  r.nav.heading = r.ndof.heading();
  Serial.println("Done calibrating");
}
/**
* Lots of tuning required
*/
void goToRamp()
{
  //Serial.println(r.haveLegoMan);
  //if(!r.haveLegoMan())
  //{
    // Chris - try to remove the nave by just rotating and finding the far wall
    // then align with the ramp as we move forward.  The ramp will never change
    // place
    // also this needs a if lego man check to do it if we are on the other side of the wall.
    
    while(r.getDistance(CENTER) > 15)
    {

      Serial.println(r.getDistance(CENTER));
      r.reverse(140);
    }
    delay(100);
    if(!r.haveLegoMan()){
        r.rotate(-90);
    }
    else{
      r.rotate(90);
    }
    delay(100);
    // // This means we are on the platform
    // while(r.getDistance(LEFT) > 10 && r.getDistance(RIGHT) > 10)
    //   r.setVelocity(.5);
    // r.setVelocity(0);
    // r.rotate(-90.0);
    while (r.ndof.gyro_.y < 15) {
      r.setVelocity(255);
      r.ndof.refresh();      
    }

    r.setVelocity(0);
    // drive forward until the ramp is engaged (we will again see a change in yaw)
  //}
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
      r.setVelocity(120, RIGHT);
    }
    else
    {
      r.setVelocity(120, LEFT);
    }
  }
  r.ndof.refresh();
  // need to determine threshholds on gyro
  while (r.ndof.gyro_.y > 10)
  {
    r.ndof.refresh();
    r.setVelocity(120);
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
    r.setVelocity(255);
}

void search()
{ 
  // this is the thing to search for lego man
  int x = 0;
  float lDist = 0;
  float rDist = 0;

  lDist = r.getDistance(LEFT);
  delay(200);
  rDist = r.getDistance(RIGHT);
  while((lDist + rDist)/2 < 160)
  {
    lDist = r.getDistance(LEFT);
    delay(200);
    rDist = r.getDistance(RIGHT);
    r.setVelocity(-.3);
  }
  while((lDist + rDist)/2 > 160)
  {
    lDist = r.getDistance(LEFT);
    delay(200);
    rDist = r.getDistance(RIGHT);
    r.setVelocity(-.3);
  }
  r.rotate(90);
  r.setBrush(true);
  // a bit of a conservative guess but yeah...
  while(x > 4)
  {
    lDist = r.getDistance(LEFT);
    delay(200);
    rDist = r.getDistance(RIGHT);
    r.setVelocity(-.3);
    if ((lDist + rDist)/2 < 20)
    {
      x++;
    }
  }
  r.rotate(90);
  // gonna need to find out a good value for this
  while(r.getDistance(CENTER) < 250 || !r.checkForLegoMan())
  {
    r.drive();
  }
  r.rotate(-90);
  // transition into go to ramp
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
State GoHome = State(goHome);
State Chill = State(chill);

FSM snr = FSM(Idle); // search and rescue state machine
// End states

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  attachInterrupt(0, killSwitch, CHANGE);
  r = Robot();
  r.setup();

  // We setup all our sensors up in this bitch.
}

// need proper implementation
void killSwitch()
{
  r.killEverything();
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
  // //r.rotate(90);
   // calibrate();
 //     r.rotate(90);
   
 //    while (true)
 //    {
 //      r.setVelocity(.0608); 
 //    }
 // // }
 //   Serial.println(r.ndof.heading());
    // goToRamp();
    r.rotate(-90);
// r.ndof.refresh();
    // Serial.println(r.ndof.gyro_.y);
    //  while (true)
    // {
    //   r.reverse(0);
    // }
 // r.setVelocity(0.02);

}

