/**
 * Robot.cpp
 */
#include "Robot.h"

Robot::Robot() : velocityRight_(0), velocityLeft_(0), brush_(0), propSpeed_(1000)
{
    usRight = UltrasonicSensor(SONAR_TRIG_RIGHT,SONAR_ECHO_RIGHT);
    usCenter = UltrasonicSensor(SONAR_TRIG_BACK,SONAR_ECHO_BACK);
    usLeft = UltrasonicSensor(SONAR_TRIG_LEFT,SONAR_ECHO_LEFT);

    lsRight = LimitSwitch(LIMIT_SWITCH_RIGHT);
    lsCenter = LimitSwitch(LIMIT_SWITCH_BACK);
    lsLeft = LimitSwitch(LIMIT_SWITCH_LEFT);
    ndof = NineDOF();
    
    mBrush = Motor(MOTOR_BRUSH_SPEED);
    mLeft = Motor(MOTOR_LEFT_DIR_A, MOTOR_LEFT_DIR_B, MOTOR_LEFT_SPEED);
    mRight = Motor(MOTOR_RIGHT_DIR_A, MOTOR_RIGHT_DIR_B, MOTOR_RIGHT_SPEED);
}

void Robot::setup()
{
  ndof.setup();
}

void Robot::setVelocity(float vel)
{
  velocityLeft_ = velocityRight_ = vel;
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
