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

class MathUtil
{
private:
  /* data */
public:

  static int multiplyWithOffset(int a, int b, int off)
  {
      Serial.print(F("mult a "));
      Serial.print(a);
      Serial.print(F(" with b "));
      Serial.print(b);
      int i = b*a;
      Serial.print(F(" to "));
      Serial.print(i);
      Serial.print(F(" div prec "));
      Serial.print(off);
      Serial.print(F(" to res "));
      Serial.println(i / off);
      return i / off;
  }
};
#endif