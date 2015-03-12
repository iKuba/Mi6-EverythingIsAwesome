/*
* Encocder.h
*/

#ifndef Encocder_h
#define Encocder_h

#include "Arduino.h"
const int pin_A = 3;  // interrupt pin
const int pin_B = 2;  // interrupt pin

volatile int lastEncoded = 0;

unsigned long prev_time;
unsigned long curr_time;
double delta_time;

double test;

double v;
double dis;
double t;
double t_sec;
int dir;
int count;

void setup()  {
  Serial.begin(9600); 
  
  curr_time = micros();
  prev_time = 0;
  dis = 18.0f*3.14f/180.0f *(17.5f/1000.0f);
  
  test = 0;
  
  dir = 0;
  t = 0;
  t_sec = 0;
  count = 0;
  curr_time = micros();

  pinMode(pin_A, INPUT);
  pinMode(pin_B, INPUT);
  digitalWrite(pin_A, HIGH); //turn pullup resistor on
  digitalWrite(pin_B, HIGH); //turn pullup resistor on

  //interrupt 0 is pin 2, interrupt 1 is pin 4
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
} 

void calculateSpeed() {
  curr_time = micros();

  if (count%4 == 0) 
  { 
    delta_time = curr_time - prev_time;
    prev_time = curr_time;
    t_sec = delta_time/1000000;
    
    if (t_sec != 0) 
    {
      v = dis/t_sec;
    }
    else 
    {
      v = 0;
    }
  }
}

void updateEncoder(){
  count++;
  int MSB = digitalRead(pin_A); //MSB = most significant bit
  int LSB = digitalRead(pin_B); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  //CW direction
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    dir = 1;
  }

  //CCW direction
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    dir = 2;
  }
  calculateSpeed();
  lastEncoded = encoded;
}