#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
 public:
  Vector2();
  Vector2(float x_inp, float y_inp);
  float x = 0;
  float y = 0;
  void normalise();
  void flipX();
  void flipY();
};
#endif