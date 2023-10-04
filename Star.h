#pragma once
#include "point.h"

const int MAX_PHASE = 255;

// **Add description, attributes, methods
class Star {
public:
   Star(Point p = Point(0.0, 0.0)) : pos(p.getX(), p.getY()), phase(random(0, MAX_PHASE)) {
   }

   Point* getPos() {
      return &pos;
   }

   int getPhase() {
      updatePhase();
      return phase;
   }

   void updatePhase() {
      if (phase > 0 && phase < MAX_PHASE)
      {
         phase++;
      }
      else {
         phase = 0;
      }
   }

private:
   Point pos;
   int phase;
};