//#include "FiniteStateMachine.h"
#include "TEMT6000.h"
#include "UltrasonicSensor.h"
#include "LimitSwitch.h"
#include "PinDefinitions.h"
#include "NineDOF.h"
#include "Wire.h"
#include "Encoder.h"
#include "EncoderISR.h"
#include "Motor.h"
#include <avr/io.h>
#include <avr/interrupt.h>

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
/*
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
State Chill = State(chill);*/

//FSM snr = FSM(Start); // search and rescue state machine
// End states

// Begin Sensors
//UltrasonicSensor us1 = UltrasonicSensor(SONAR_TRIG1,SONAR_ECHO1);
/*UltrasonicSensor us2 = UltrasonicSensor(SONAR_TRIG2,SONAR_ECHO2);
UltrasonicSensor us3 = UltrasonicSensor(SONAR_TRIG3,SONAR_ECHO3);

TEMT6000 reciever_left = TEMT6000(RECEIVER_LEFT);
TEMT6000 reciever_right = TEMT6000(RECEIVER_RIGHT);


NineDOF ndof = NineDOF();*/

// End Sensors

Motor mRight = Motor(MOTOR_LEFT_DIR_A,MOTOR_LEFT_DIR_B,MOTOR_LEFT_ENABLE);
Motor mLeft = Motor(MOTOR_RIGHT_DIR_A,MOTOR_RIGHT_DIR_B,MOTOR_RIGHT_ENABLE);


LimitSwitch ls_left = LimitSwitch(LIMIT_SWITCH_LEFT);
LimitSwitch ls_mid = LimitSwitch(LIMIT_SWITCH_MID);
LimitSwitch ls_right = LimitSwitch(LIMIT_SWITCH_RIGHT);

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
  //ndof.setup();

  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 15624;
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  // enable global interrupts:
  sei();

  // We setup all our sensors up in this bitch.

  attachInterrupt(0, updateEncoder_R, CHANGE); 
  attachInterrupt(1, updateEncoder_R, CHANGE); 
  attachInterrupt(4, updateEncoder_L, CHANGE);
  attachInterrupt(5, updateEncoder_L, CHANGE);
}

ISR(TIMER1_COMPA_vect)
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

  //Running Motors
  mLeft.setVelocity(255, 1);
  mRight.setVelocity(255, 1);

  //Testing Encoders
  Serial.print("Right Encoder: ");
  Serial.println(e_right.speed,4);
  Serial.print("Left Encoder: ");
  Serial.println(e_left.speed,4);
  Serial.println();

  //Testing Limit Switches
  Serial.print("Left Limit Switch: ");
  if (ls_left.query())
  {
    Serial.println("HIT");
  }
  else
  {
    Serial.println("NOT HIT");
  }

  Serial.print("Right Limit Switch: ");
  if (ls_right.query())
  {
    Serial.println("HIT");
  }
  else
  {
    Serial.println("NOT HIT");
  }

  Serial.print("Middle Limit Switch: ");
  if (ls_mid.query())
  {
    Serial.println("HIT");
  }
  else
  {
    Serial.println("NOT HIT");
  }

  delay(1000);
}

