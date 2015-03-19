/**
 * NineDOF.cpp
 */
#include "Arduino.h"
#include "NineDOF.h"
#include "Wire.h"

NineDOF::NineDOF() : I2C()
{
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
	buildGyro();
	readFrom(COMP_ADDR, COMP_REG, 6);
	buildComp();
	readFrom(ACEL_ADDR, ACEL_REG, 6);
	buildAccel();
}

void NineDOF::buildGyro()
{
  gyro_.x = -1 * ((((int) buffer_[2]) << 8) | buffer_[3]) - GYRO_AVERAGE_OFFSET_X;    // X axis (internal sensor -y axis)
  gyro_.y = -1 * ((((int) buffer_[0]) << 8) | buffer_[1]) - GYRO_AVERAGE_OFFSET_Y;    // Y axis (internal sensor -x axis)
  gyro_.z = -1 * ((((int) buffer_[4]) << 8) | buffer_[5]) - GYRO_AVERAGE_OFFSET_Z;    // Z axis (internal sensor -z axis)
}

void NineDOF::buildComp()
{
  comp_.x = (((int) buffer_[0]) << 8) | buffer_[1];         // X axis (internal sensor x axis)
  comp_.y = -1 * ((((int) buffer_[4]) << 8) | buffer_[5]);  // Y axis (internal sensor -y axis)
  comp_.z = -1 * ((((int) buffer_[2]) << 8) | buffer_[3]);  // Z axis (internal sensor -z axis)
  comp_.x = (comp_.x - MAGN_X_OFFSET) * MAGN_X_SCALE;
  comp_.y = (comp_.y - MAGN_Y_OFFSET) * MAGN_Y_SCALE;
  comp_.z = (comp_.z - MAGN_Z_OFFSET) * MAGN_Z_SCALE;
}

void NineDOF::buildAccel()
{
  accel_.x = ((buffer_[1] <<8) | buffer_[0] - ACCEL_X_OFFSET) * ACCEL_X_SCALE/256.0*9.81;
  accel_.y = ((buffer_[3] <<8) | buffer_[2] - ACCEL_Y_OFFSET) * ACCEL_Y_SCALE/256.0*9.81;
  accel_.z = ((buffer_[5] <<8) | buffer_[4] - ACCEL_Z_OFFSET) * ACCEL_Z_SCALE/256.0*9.81;
}

float NineDOF::heading()
{
  refresh();
  float heading = atan2(comp_.y, comp_.x);

  // Correct for when signs are reversed.
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG; //radians to degrees
}


	