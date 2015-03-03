/**
 * Look at me I'm a header file
 *
 * I2C.h
 */
#ifndef I2C_h
#define I2C_h

#include "Arduino.h"
#include <Wire.h>

class I2C
{
public:
  I2C();


protected:
  void writeTo(int device, byte address, byte value);

  void readFrom(int device, byte address, int num);

  byte buffer_[6];
};

#endif
