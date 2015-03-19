/**
 * Robot.cpp
 */
#include "Robot.h"

 #define PWM(vel) (int) (1000*vel+60.8)

UltrasonicSensor Robot::usRight;
UltrasonicSensor Robot::usCenter;
UltrasonicSensor Robot::usLeft;

LimitSwitch Robot::lsRight;
LimitSwitch Robot::lsCenter;
LimitSwitch Robot::lsLeft;
NineDOF Robot::ndof;

Motor Robot::mBrush;
Motor Robot::mLeft;
Motor Robot::mRight;

Accelerometer Robot::accLeft;
Accelerometer Robot::accRight;

Servo Robot::prop_;

Robot::Robot() : velocityRight_(0), velocityLeft_(0), brush_(0){}

void Robot::setup()
{
  usRight = UltrasonicSensor(SONAR_TRIG_RIGHT,SONAR_ECHO_RIGHT);
  usCenter = UltrasonicSensor(SONAR_TRIG_BACK,SONAR_ECHO_BACK);
  usLeft = UltrasonicSensor(SONAR_TRIG_LEFT,SONAR_ECHO_LEFT);

  lsRight = LimitSwitch(LIMIT_SWITCH_RIGHT);
  lsCenter = LimitSwitch(LIMIT_SWITCH_BACK);
  lsLeft = LimitSwitch(LIMIT_SWITCH_LEFT);
  mBrush = Motor(MOTOR_BRUSH_SPEED);
  mLeft = Motor(MOTOR_LEFT_DIR_A, MOTOR_LEFT_DIR_B, MOTOR_LEFT_SPEED);
  mRight = Motor(MOTOR_RIGHT_DIR_A, MOTOR_RIGHT_DIR_B, MOTOR_RIGHT_SPEED);

  accLeft = Accelerometer(ACCEL_LEFT_GUIDE);
  accRight = Accelerometer(ACCEL_RIGHT_GUIDE);

  ndof = NineDOF();

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
  mLeft.setVelocity(abs(velocityLeft_), velocityLeft_ >= 0);
  mRight.setVelocity(abs(velocityRight_), velocityRight_ >= 0);
  mBrush.setVelocity(brush_?100:0);
}

void Robot::setVelocity(float vel)
{
  velocityLeft_ = velocityRight_ = PWM(vel);
  drive();
}

void Robot::rotate(float angle)
{ 
  float heading = ndof.heading();

  // going to need to test this to make sure we can do it
  while (heading+angle > ndof.heading())
  {
    mRight.setVelocity(PWM(.1), (angle > 0)?0:1);
    mLeft.setVelocity(PWM(.1), (angle > 0)?1:0);
  }
  mRight.setVelocity(0,1);
  mLeft.setVelocity(0,1);
}

void Robot::propOn(bool on)
{
  if (on)
  {
    prop_.write(90);
  }
  else
  {
    prop_.write(45);
  }
}

void Robot::setVelocity(float vel, POSITION pos)
{
  if (pos == LEFT)
  {
    velocityLeft_ = PWM(vel);
  }
  else if (pos == RIGHT)
  {
    velocityRight_ = PWM(vel);
  }
  else
  {
    Serial.println("This is retarded don't tell me center");
  }
  drive();
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
