/**
 * Look at me I'm a header file
 *
 * INS.h
 */
#ifndef INS_h
#define INS_h

#include "NineDOF.h"
#include <Time.h>

class INS
{
public:
  INS(NineDOF ndof);

  void calculate();

private:
  NineDOF ndof_;

  float prev_time_;

  float x,y,z,dx,dy,dz,ddx,ddy,ddz;
  void integratePos();
  void integrateOrientation();

};

#endif
