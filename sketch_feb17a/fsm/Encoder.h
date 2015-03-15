/**
 * Look at me I'm a header file
 *
 * Encoder.h
 */
#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"
class Encoder
{
public:
  /**
   * Constructor for the limit switch
   */
   Encoder(int pinA, int pinB);

  int direction;
  int count;
  int lastEncoded;
  int speed;

  void calculateSpeed();

private:
  int pinA_;
  int pinB_;

  double curr_time_;
  double prev_time_;
  double delta_time_;
  int time_;
};

#endif
