/*
* Encocder.h
*/

#ifndef Encocder_h
#define Encocder_h

#include "Arduino.h"
const int pin_A = 3;  // interrupt pin
const int pin_B = 2;  // interrupt pin

int dir = 0;
int count;
int count_old;
double num_ticks = 0;
double distance = 0;

void setup()  {
  Serial.begin(9600); 
  count = 0;
  count_old = 0;
  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  digitalWrite(pin_A, HIGH); //turn pullup resistor on
  digitalWrite(pin_B, HIGH); //turn pullup resistor on
  //interrupt 0 is pin 2, interrupt 1 is pin 4
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
} 

void updateEncoder(){
  int MSB = digitalRead(pin_A); //MSB = most significant bit
  int LSB = digitalRead(pin_B); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    count ++;
    dir = 2;
  }
      
  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    count --;
    dir = 1;
  }
  lastEncoded = encoded; //store this value for next time
}