/**
 * Look at me I'm a header file
 *
 * NineDOF.h
 */
#ifndef NineDOF_h
#define NineDOF_h

#include "Arduino.h"
#include <Wire.h>
#include "I2C.h"


struct Raw{
  int x,y,z,offx,offy,offz;
};

class NineDOF : public I2C
{
public:
  NineDOF();
  void refresh();
  void setup();
  Raw gyro_, acel_, comp_;
private:
  static const int GYRO_ADDR = 0x68;
  static const int COMP_ADDR = 0x1E;
  static const int ACEL_ADDR = 0x53;
  static const int GYRO_REG = 0x1D;
  static const int COMP_REG = 0x03;
  static const int ACEL_REG = 0x32;
  static const float ACEL_X_SCALE = (256.0f / (287 - 3));
  static const float ACEL_Y_SCALE = (256.0f / (286 - .5));
  static const float ACEL_Z_SCALE = (256.0f / (277 - 4));

  void build(Raw *value);
  void buildAccel();
};

#endif
