#ifndef POINT_H
#define POINT_H

class Point
{
 private:
  double x;
  double y;

 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};

#endif
