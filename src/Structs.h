#ifndef STRUCTS_H
#define STRUCTS_H


namespace Structs
{
  // helpful structs for positions and rects
  struct XY
  {
    double x = 0;
    double y = 0;
  };

  struct Rect
  {
    double x      = 0;
    double y      = 0;
    double width  = 0;
    double height  = 0;
  };
}


#endif // !STRUCTS_H