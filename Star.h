#pragma once
#include "point.h"

// **Add description, attributes, methods
class Star {
public:
   Star(Point p = Point(0.0, 0.0)) : pos(p.getX(), p.getY()), phase(random(0, 255)) {
   }

   Point* getPos() {
      return &pos;
   }

   int getPhase() {
      return phase;
   }

   void updatePhase() {
   
   }

private:
   Point pos;
   int phase;
};