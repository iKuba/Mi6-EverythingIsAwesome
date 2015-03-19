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

#define ACCEL_X_MIN ((float) -27)
#define ACCEL_X_MAX ((float) 19)
#define ACCEL_Y_MIN ((float) -28)
#define ACCEL_Y_MAX ((float) 76)
#define ACCEL_Z_MIN ((float) -262)
#define ACCEL_Z_MAX ((float) 268)

#define MAGN_X_MIN ((float) -812)
#define MAGN_X_MAX ((float) 733)
#define MAGN_Y_MIN ((float) -452)
#define MAGN_Y_MAX ((float) 779)
#define MAGN_Z_MIN ((float) -651)
#define MAGN_Z_MAX ((float) 790)
#define GRAVITY 1.0f

 // Sensor calibration scale and offset values
#define ACCEL_X_OFFSET 3
#define ACCEL_Y_OFFSET 0
#define ACCEL_Z_OFFSET 2
#define ACCEL_X_SCALE (256.0f / (287 - 3))
#define ACCEL_Y_SCALE (256.0f / (286 - .5))
#define ACCEL_Z_SCALE  (256.0f / (277 - 4))

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0f)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0f)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0f)
#define MAGN_X_SCALE (100.0f / (MAGN_X_MAX - MAGN_X_OFFSET))
#define MAGN_Y_SCALE (100.0f / (MAGN_Y_MAX - MAGN_Y_OFFSET))
#define MAGN_Z_SCALE (100.0f / (MAGN_Z_MAX - MAGN_Z_OFFSET))

#define GYRO_AVERAGE_OFFSET_X ((float) -82.73)
#define GYRO_AVERAGE_OFFSET_Y ((float) 17.29)
#define GYRO_AVERAGE_OFFSET_Z ((float) -13.01)

// Gain for gyroscope (ITG-3200)
#define GYRO_GAIN 0.06957 // Same gain on all axes
#define GYRO_SCALED_RAD(x) (x * TO_RAD(GYRO_GAIN)) // Calculate the scaled gyro readings in radians per second


struct Raw{
  float x,y,z,offx,offy,offz;
};

class NineDOF : public I2C
{
public:
  NineDOF();
  void refresh();
  void setup();
  float heading();
  Raw gyro_, accel_, comp_;
private:
  static const int GYRO_ADDR = 0x68;
  static const int COMP_ADDR = 0x1E;
  static const int ACEL_ADDR = 0x53;
  static const int GYRO_REG = 0x1D;
  static const int COMP_REG = 0x03;
  static const int ACEL_REG = 0x32;
  void buildGyro();
  void buildComp();
  void buildAccel();
};

#endif
