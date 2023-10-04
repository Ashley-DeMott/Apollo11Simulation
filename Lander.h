#pragma once
#include "point.h"

// **Add description, attributes, methods
class Lander {
public:
   Lander() : pos(0.0, 0.0) {
   }
   
   Point* getPos() {
      return &pos;
   }

   void addPos(double x, double y) {
      this->pos.addX(x);
      this->pos.addY(y);
   }

private:
   Point pos; // The position of the Lander

};