#pragma once
// Objects within the Simulation
#include "ground.h"
#include "Star.h"
#include "Lander.h"

using namespace std;
/* TODO: Add descriptions/comments for each method */


/*************************************************************************
 * Simulation
 * ** Add description, holds all data
 *************************************************************************/
class Simulation
{
public:
   Simulation(const Point& ptUpperRight) : ptUpperRight(ptUpperRight), ground(ptUpperRight), lm(Point((ptUpperRight.getX() / 2.0), ptUpperRight.getY() / 2.0)), star(Point(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0)) {
      // Point((ptUpperRight.getX() - (ptUpperRight.getX() / 2.0)), ptUpperRight.getY() - (ptUpperRight.getY() / 4.0)) // Middle upper
      // Point(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0) // 20 down from the right hand corner (on the right edge)
   }

   // **Add all public methods

   Point* getUpperRight() {
      return &ptUpperRight;
   }

   void moveLM(double x, double y) {
      this->lm.addPos(x, y);
   }

   Point* getLMPos() {
      return lm.getPos();
   }

   double getLMAngle() {
      return lm.getAngle();
   }

   Star* getStar() {
      return &star;
   }

   const void drawGround(ogstream &out) {
      ground.draw(out);
   }

private:
   Point ptUpperRight;   // The upper right corner of the screen

   Lander lm;
   Star star; // Only have one Star for now, will contain all within a list/vector/array/etc
   //list<Star*> stars;


   Ground ground;   

   // **Add all private methods
};
