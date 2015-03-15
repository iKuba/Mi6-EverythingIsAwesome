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

  unsigned long prev_time;
  unsigned long curr_time;
  double delta_time;
  double distance;
  double speed;
  double time;

  int direction;
  int count;
  int lastEncoded;

  double calculateSpeed(double curr_time, double prev_time, double delta_time, double time);

private:
  int pinA_;
  int pinB_;

  double curr_time_;
  double prev_time_;
  double delta_time_;
  double speed_;
  int time_;
  int count_;
};

#endif
