/**
 * Robot.cpp
 */
#include "Robot.h"

Robot::Robot()
{
    usRight = UltrasonicSensor(SONAR_TRIG_RIGHT,SONAR_ECHO_RIGHT);
    usCenter = UltrasonicSensor(SONAR_TRIG_BACK,SONAR_ECHO_BACK);
    usLeft = UltrasonicSensor(SONAR_TRIG_LEFT,SONAR_ECHO_LEFT);

    lsRight = LimitSwitch(LIMIT_SWITCH_RIGHT);
    lsCenter = LimitSwitch(LIMIT_SWITCH_BACK);
    lsLeft = LimitSwitch(LIMIT_SWITCH_LEFT);
    ndof = NineDOF();
}

void Robot::setup()
{
  ndof.setup();
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
    return (lsLeft.query() << 2) | (lsCenter << 1) | (lsRight);
}
