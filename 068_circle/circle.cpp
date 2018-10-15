#include "circle.h"

#include <algorithm>
#include <cmath>

#include "point.h"

Circle::Circle(Point a, double r) : center(a), radius(r) {}
void Circle::move(double dx, double dy) {
  center.Point::move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = center.Point::distanceFrom(otherCircle.center);
  if (distance >= radius + otherCircle.radius) {
    return 0;
  }
  else if (distance <= std::abs(radius - otherCircle.radius)) {
    double minR = std::min(radius, otherCircle.radius);
    double res = M_PI * minR * minR;
    return res;
  }
  else {
    double angle1 =
        acos((radius * radius + distance * distance - otherCircle.radius * otherCircle.radius) /
             (2 * distance * radius));
    double angle2 =
        acos((otherCircle.radius * otherCircle.radius + distance * distance - radius * radius) /
             (2 * distance * otherCircle.radius));
    return radius * radius * angle1 + otherCircle.radius * otherCircle.radius * angle2 -
           sin(angle1) * radius * distance;
  }
}
