/**
 * Robot.cpp
 */
#include "Robot.h"

 #define PWM(vel) (int) (1000*vel-60.8)

UltrasonicSensor Robot::usRight;
UltrasonicSensor Robot::usCenter;
UltrasonicSensor Robot::usLeft;

LimitSwitch Robot::lsRight;
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
  lsLeft = LimitSwitch(LIMIT_SWITCH_LEFT);
  mBrush = Motor(MOTOR_BRUSH_SPEED);
  mLeft = Motor(MOTOR_LEFT_DIR_A, MOTOR_LEFT_DIR_B, MOTOR_LEFT_SPEED);
  mRight = Motor(MOTOR_RIGHT_DIR_A, MOTOR_RIGHT_DIR_B, MOTOR_RIGHT_SPEED);

  accLeft = Accelerometer(ACCEL_LEFT_GUIDE);
  accRight = Accelerometer(ACCEL_RIGHT_GUIDE);

  ndof = NineDOF();

  ndof.setup();
}

void Robot::killEverything()
{
  propOn(false);
  setVelocity(0);
}

bool Robot::haveLegoMan(){
  return legoMan_;
}

bool Robot::checkForLegoMan()
{
  Serial.println("Left switch " + String(lsLeft.query()));
  Serial.println("Right switch " + String(lsRight.query()));
}

bool Robot::guardDown(POSITION pos)
{
  if (pos == LEFT)
  {
    Serial.println("Left: " + String(accLeft.getPosition()));
    return accLeft.getPosition() < 1;
  }
  else if (pos == RIGHT)
  {
    Serial.println("Right " + String(accRight.getPosition()));
    return accRight.getPosition() < 1;
  }
  else
  {
    Serial.println("No middle accel...");
    return false;
  }
}

void Robot::drive()
{
  mLeft.setVelocity(velocityLeft_, 1);
  mRight.setVelocity(velocityRight_, 1);
  mBrush.setVelocity(255);//brush_?255:0);
}

void Robot::setVelocity(float vel)
{
  velocityLeft_ = velocityRight_ = PWM(vel);
  drive();
}

void Robot::rotate(float angle)
{ 
  float prevHeading = ndof.heading();
  float desiredHeading = prevHeading - angle;
  if (desiredHeading > 360)
  {
    desiredHeading-=360;
    while(!(prevHeading+1 > desiredHeading && ndof.heading()-1 < desiredHeading))
    {
      mRight.setVelocity(255, 0);
      mLeft.setVelocity(255, 1);
      prevHeading = ndof.heading();
    }
  }
  else if (desiredHeading < 0)
  {
    desiredHeading+=360;
    while(!(prevHeading-1 < desiredHeading && ndof.heading()+1 > desiredHeading))
    {
      mRight.setVelocity(255, 1);
      mLeft.setVelocity(255, 0);
      prevHeading = ndof.heading();
    }
  }
  else if (angle < 0)
  {
    while(!(prevHeading-1 < desiredHeading && ndof.heading()+1 > desiredHeading))
    {
      mRight.setVelocity(255, 1);
      mLeft.setVelocity(255, 0);                      
      prevHeading = ndof.heading();
    }
  }
  else
  {
    while(!(prevHeading+1 > desiredHeading && ndof.heading()-1 < desiredHeading))
    {
      mRight.setVelocity(255, 0);
      mLeft.setVelocity(255, 1);
      prevHeading = ndof.heading();
    }
  }
  Serial.println(ndof.heading());
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
