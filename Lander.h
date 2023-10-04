#pragma once
#include "point.h"

// **Add description, attributes, methods
class Lander {
public:
   Lander() : pos(0, 0) {
   }
   
   Point* getPos() {
      return &pos;
   }

   void addPos(double x, double y) {
      this->pos.addX(x);
      this->pos.addY(y);
   }

   void setPos(double x, double y) {
      this->pos.setX(x);
      this->pos.setY(y);
   }

private:
   Point pos;

};