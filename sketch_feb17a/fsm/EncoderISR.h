/*
* LimitSwitch.h
*/
#include "Encoder.h"

#ifndef EncoderISR_h
#define EncoderISR_h

#include "Arduino.h"
#include "PinDefinitions.h"

Encoder e_left = Encoder(ENCODER_LEFT_A, ENCODER_LEFT_B);
Encoder e_right = Encoder(ENCODER_RIGHT_A, ENCODER_RIGHT_B);

//Encoder 1 = RIGHT ENCODER
void updateEncoder_1(int &lastEncoded_1, int count_1, int &dir_1, int pinA, int pinB){
  count_1++;
  int MSB = digitalRead(pinA); //MSB = most significant bit
  int LSB = digitalRead(pinB); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded_1 << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    dir_1 = 1;
  }

  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    dir_1 = 2;
  }
  calculateSpeed();
  lastEncoded_1 = encoded;
}

//Encoder 2 = LEFT ENCODER
void updateEncoder_2(int &lastEncoded_2, int count_2, int &dir_2, int pinA, int pinB){
  count_2++;
  int MSB = digitalRead(pinA); //MSB = most significant bit
  int LSB = digitalRead(pinB); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded_2 << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    dir_2 = 1;
  }

  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    dir_2 = 2;
  }
  calculateSpeed();
  lastEncoded_2 = encoded;
}

#endif