/**
 * INS.cpp
 */
#include "INS.h"

INS::INS(NineDOF ndof) : ndof_(ndof)
{
    x = y = z = dx = dy = dz = 0;
    ndof_.refresh();
    ddx = ndof_.acel_.x;
    ddy = ndof_.acel_.y;
    ddz = ndof_.acel_.z;
    prev_time_ = now();
}

void INS::calculate()
{
  float dt = now() - prev_time_;
  ndof_.refresh();
  dx+= (ndof_.acel_.x + ddx)/2.0f * dt;
  x+=dx*dt;

  dy+= (ndof_.acel_.y + ddy)/2.0f * dt;
  y+=dy*dt;

  dy+= (ndof_.acel_.y + ddy)/2.0f * dt;
  y+=dy*dt;
}