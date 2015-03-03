/**
 * NineDOF.cpp
 */
#include "Arduino.h"
#include "NineDOF.h"
#include "Wire.h"

NineDOF::NineDOF() : I2C()
{
    gyro_.offx = -6;
    gyro_.offy = 75;
    gyro_.offz = 15;

    comp_.offx = 0;
    comp_.offy = 0;
    comp_.offz = 0;

    acel_.offx = 3;
    acel_.offy = 0;
    acel_.offz = 2;
}

void NineDOF::setup()
{
	writeTo(GYRO_ADDR,0x16,B00011011);
  delay(10);   
  writeTo(COMP_ADDR, 0x01, B00100000);
  delay(10);
  writeTo(COMP_ADDR, 0x02, B00000000);
  delay(10);
  writeTo(ACEL_ADDR,0x2D,B00000000);//set everything to zero, enters standby mode, which is recommended before changing things
  delay(10);
  writeTo(ACEL_ADDR,0x31, B00001001); //set to 4g, (can be 0x00001011 for 16g) with a full scale resolution
  delay(10);
  writeTo(ACEL_ADDR,0x2D,8);
}

void NineDOF::refresh()
{
	readFrom(GYRO_ADDR, GYRO_REG, 6);
	build(&gyro_);
	readFrom(COMP_ADDR, COMP_REG, 6);
	build(&comp_);
	readFrom(ACEL_ADDR, ACEL_REG, 6);
	buildAccel();
}

void NineDOF::build(Raw * value)
{
  value->x = ((buffer_[0] <<8) | buffer_[1]) - value->offx;
  value->y = ((buffer_[2] <<8) | buffer_[3]) - value->offy;
  value->z = ((buffer_[4] <<8) | buffer_[5]) - value->offz;
}

void NineDOF::buildAccel()
{
  acel_.x = ((buffer_[1] <<8) | buffer_[0] - (acel_).offx) * ACEL_X_SCALE;
  acel_.y = ((buffer_[3] <<8) | buffer_[2] - (acel_).offy) * ACEL_Y_SCALE;
  acel_.z = ((buffer_[5] <<8) | buffer_[4] - (acel_).offz) * ACEL_Z_SCALE;
}


	