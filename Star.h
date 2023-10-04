#pragma once
#include "point.h"

// **Add description, attributes, methods
class Star {
public:
   Star() : pos(0.0, 0.0) {

   }

   Point* getPos() {
      return &pos;
   }

private:
   Point pos;
};