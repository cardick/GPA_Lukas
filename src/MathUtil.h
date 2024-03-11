#include <Arduino.h>
#ifndef MathUtil_h
#define MathUtil_h

#define x_axis_value(var) \
    ((var & Front) != 0 ? ((var & Back) != 0 ? 0 : 1) : ((var & Back) != 0 ? -1 : 0))

#define y_axis_value(var) \
    ((var & Left) != 0 ? ((var & Right) != 0 ? 0 : 1) : ((var & Right) != 0 ? -1 : 0))

#define z_axis_value(var) \
    ((var & Up) != 0 ? ((var & Down) != 0 ? 0 : 1) : ((var & Down) != 0 ? -1 : 0))

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