/**
 * I2C.cpp
 */
#include "Arduino.h"
#include "Wire.h"
#include "I2C.h"

I2C::I2C(){}

void I2C::writeTo(int device, byte address, byte val)
{
    Wire.beginTransmission(device);
    Wire.write(address);
    Wire.write(val);
    Wire.endTransmission();
}

void I2C::readFrom(int device, byte address, int num)
{
	Wire.beginTransmission(device);
    Wire.write(address);
    Wire.endTransmission();
  
    Wire.beginTransmission(device);
    Wire.requestFrom(device,num);
    if(Wire.available()==num)
      for(int x = 0; x< num; x++)
       buffer_[x] = Wire.read();
    Wire.endTransmission();
}