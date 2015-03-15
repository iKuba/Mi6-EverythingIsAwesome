/*
* EncoderISR.h
*/
#include "Encoder.h"

#ifndef EncoderISR_h
#define EncoderISR_h

#include "Arduino.h"
#include "PinDefinitions.h"

Encoder e_left = Encoder(ENCODER_LEFT_A, ENCODER_LEFT_B);
Encoder e_right = Encoder(ENCODER_RIGHT_A, ENCODER_RIGHT_B);

//Encoder 1 = RIGHT ENCODER
void updateEncoder_R(){
  e_right.count++;
  int MSB = digitalRead(ENCODER_RIGHT_A); //MSB = most significant bit //this what does this do??
  int LSB = digitalRead(ENCODER_RIGHT_B); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (e_right.lastEncoded << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    e_right.direction = 1;
  }

  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    e_right.direction = 2;
  }

  e_right.calculateSpeed();
  e_right.lastEncoded = encoded;
}

//Encoder 2 = LEFT ENCODER
void updateEncoder_L(){
  e_left.count++;
  int MSB = digitalRead(ENCODER_LEFT_A); //MSB = most significant bit
  int LSB = digitalRead(ENCODER_LEFT_B); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (e_left.lastEncoded << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    e_left.direction = 1;
  }

  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    e_left.direction = 2;
  }
  e_left.calculateSpeed();
  e_left.lastEncoded = encoded;
}

#endif