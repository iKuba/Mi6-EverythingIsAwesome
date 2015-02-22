/**
 * Look at me I'm a header file
 *
 * TEMT6000.h
 */
#ifndef TEMT6000_h
#define TEMT6000_h

#include "Arduino.h"
class TEMT6000
{
public:
  /**
   * Constructor for the light intensity sensor
   */
  TEMT6000(int temt6000pin);

  /**
   * Asking light sensor for intensity 0 to 1023
   */
  int query();

private:
  int temt6000pin_;
};

#endif
