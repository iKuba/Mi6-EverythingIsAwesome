/**
 * Robot.cpp
 */
#include "Robot.h"

UltrasonicSensor Robot::usRight = UltrasonicSensor(SONAR_TRIG_RIGHT,SONAR_ECHO_RIGHT);
UltrasonicSensor Robot::usCenter = UltrasonicSensor(SONAR_TRIG_BACK,SONAR_ECHO_BACK);
UltrasonicSensor Robot::usLeft = UltrasonicSensor(SONAR_TRIG_LEFT,SONAR_ECHO_LEFT);

LimitSwitch Robot::lsRight = LimitSwitch(LIMIT_SWITCH_RIGHT);
LimitSwitch Robot::lsCenter = LimitSwitch(LIMIT_SWITCH_BACK);
LimitSwitch Robot::lsLeft = LimitSwitch(LIMIT_SWITCH_LEFT);
NineDOF  Robot::ndof = NineDOF();

Motor Robot::mBrush = Motor(MOTOR_BRUSH_SPEED);
Motor Robot::mLeft = Motor(MOTOR_LEFT_DIR_A, MOTOR_LEFT_DIR_B, MOTOR_LEFT_SPEED);
Motor Robot::mRight = Motor(MOTOR_RIGHT_DIR_A, MOTOR_RIGHT_DIR_B, MOTOR_RIGHT_SPEED);

Accelerometer Robot::accLeft = Accelerometer(ACCEL_LEFT_GUIDE);
Accelerometer Robot::accRight = Accelerometer(ACCEL_RIGHT_GUIDE);

Robot::Robot() : velocityRight_(0), velocityLeft_(0), brush_(0), propSpeed_(1000){}

void Robot::setup()
{
  ndof.setup();
}

bool Robot::haveLegoMan(){
  return legoMan_;
}

bool Robot::checkForLegoMan()
{
  // check things if we have lego man set legoMan_
}

bool Robot::guardDown(POSITION pos)
{
  if (pos == LEFT)
  {
    return accLeft.getPosition() > 0;
  }
  else if (pos == RIGHT)
  {
    return accRight.getPosition() > 0;
  }
  else
  {
    Serial.println("No middle accel...");
    return false;
  }
}

void Robot::drive()
{
  mLeft.setVelocity(velocityLeft_, LEFT);
  mRight.setVelocity(velocityRight_, RIGHT);
  mBrush.setVelocity(brush_?100:0);
  prop_.writeMicroseconds(propSpeed_);
}

void Robot::setVelocity(float vel)
{
  velocityLeft_ = velocityRight_ = vel;
}

void Robot::rotate(float angle)
{ 
  setVelocity(0);
  // now enter a loop which condition is to rotate left or right based on
  // angle by setting motors to equal and oposite things
  // this will cause us to turn in place
}

void Robot::propOn(bool on)
{
  if (on)
  {
    for(propSpeed_ = 0; propSpeed_ < 1000; propSpeed_++)
    {
      prop_.writeMicroseconds(propSpeed_);
      // delaying 1 ms for now
      delay(5);
    }
  }
  else
  {
    propSpeed_ = 1000;
    prop_.writeMicroseconds(propSpeed_);
  }
}

void Robot::setVelocity(float vel, POSITION pos)
{
  if (pos == LEFT)
  {
    velocityLeft_ = vel;
  }
  else if (pos == RIGHT)
  {
    velocityRight_ = vel;
  }
  else
  {
    Serial.println("This is retarded don't tell me center");
  }
}

void Robot::setBrush(bool brush)
{
  brush_ = brush;
}

float Robot::getDistance(POSITION pos)
{
  if (pos == LEFT)
  {
    return usLeft.query();
  }
  else if (pos == RIGHT)
  {
    return usRight.query();
  }
  return usCenter.query();
}

uint8_t Robot::switches()
{
    return (lsLeft.query() << 2) | (lsCenter.query() << 1) | (lsRight.query());
}
