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
   Simulation(const Point& ptUpperRight) :      
      ground(ptUpperRight)
   {
      // Intial parameters are in comments for now
      lm = Lander(); // angle(0.0), ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
      star = Star(); // ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0) //phase = random(0, 255);
   }

   // **Add all public methods

   void moveLM(double x, double y) {
      this->lm.addPos(x, y);
   }

   Point* getLMPos() {
      return lm.getPos();
   }

private:
   Point ptUpperRight;   // size of the screen


   Lander lm;
   Star star; // Only have one Star for now, will contain all within a list/vector/array/etc
   //list<Star*> stars;


   Ground ground;   

   // **Add all private methods
};
