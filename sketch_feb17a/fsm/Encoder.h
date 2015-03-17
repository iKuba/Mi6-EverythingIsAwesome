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

  bool direction;
  int count;
  volatile int lastEncoded;
  double speed;

  void calculateSpeed();

private:
  int pinA_;
  int pinB_;

  unsigned long curr_time_;
  unsigned long prev_time_;
  double delta_time_;
  double time_;
};

#endif
