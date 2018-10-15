#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"

class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(Point a, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
