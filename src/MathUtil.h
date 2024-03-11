#include <Arduino.h>
#ifndef MathUtil_h
#define MathUtil_h

/// @brief Direction flags for the base directions.
enum Direction
{
  Zero = 0 << 0,
  Front = 1 << 0,
  Left = 1 << 1,
  Up = 1 << 2,
  Back = 1 << 3,
  Right = 1 << 4,
  Down = 1 << 5
};

#endif