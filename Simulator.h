#pragma once
#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"

// Objects within the Simulation
#include "ground.h"
#include "Star.h"
#include "Lander.h"

using namespace std;


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
      lm = Lander(); // angle(0.0), ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
      star = Star(); // ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0) //phase = random(0, 255);
   }

   // **Add all public methods

private:
   Point ptUpperRight;   // size of the screen


   Lander lm;
   Star star; // Only have one Star for now, will add more later
   //list<Star*> stars;


   Ground ground;   

   // **Add all private methods
};
