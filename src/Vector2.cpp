#include "Vector2.h"
#include <math.h>

Vector2::Vector2() {}

Vector2::Vector2(float x_inp, float y_inp)
{
  x = x_inp;
  y = y_inp;
}

void Vector2::normalise()
{
    // check that the vector is not 0, if so normalise. 
  if (x + y != 0)
  {
    float magnitude = sqrt(x * x + y * y);
    x               = x / magnitude;
    y               = y / magnitude;
  }
}

void Vector2::flipX()
{
  x = -x;
}

void Vector2::flipY()
{
  y = -y;
}