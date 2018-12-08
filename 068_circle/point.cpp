#include "point.h"

#include <cmath>
Point::Point() : x(0), y(0) {}
void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}
double Point::distanceFrom(const Point & p) {
  double xsquare = (p.x - x) * (p.x - x);
  double ysquare = (p.y - y) * (p.y - y);
  double res = sqrt(xsquare + ysquare);
  return res;
}
