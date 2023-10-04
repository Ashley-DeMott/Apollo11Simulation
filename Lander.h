#pragma once
#include "point.h"

// **Add description, attributes, methods
class Lander {
public:
   Lander(Point p = Point(0.0, 0.0)) : pos(p.getX(), p.getY()), angle(0.0) {
   }
   
   Point* getPos() {
      return &pos;
   }

   void addPos(double x, double y) {
      this->pos.addX(x);
      this->pos.addY(y);
   }

   double getAngle() {
      return angle;
   }

private:
   Point pos; // The position of the Lander
   double angle;

};