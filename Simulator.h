#pragma once
// Objects within the Simulation
#include "ground.h"
#include "Star.h"
#include "Lander.h"

// List for Stars
#include <list>

using namespace std;

#define TIME_INTERVAL 0.1       // How often callBack is called, the speed of the Simulation
#define SAFE_LANDING_VEL 4.0    // The maximum velocity the Lander can safely land

const int  NUM_STARS = 50;      // The number of Stars to create

/*************************************************************************
 * Simulator
 * Represents a simulation environment, including ground, stars, and a lunar module.
 *************************************************************************/
class Simulator
{
public:
    // Constructor to initialize the different parts of the simulator
   Simulator(const Point& ptUpperRight) : ptUpperRight(ptUpperRight), ground(ptUpperRight), lm(Point((ptUpperRight.getX()) - 20.0, ptUpperRight.getY() - 20.0)) {
      createStars(); // Create all the Stars to be displayed
   }

   // Get the upper right point of the simulator (The window's size)
   Point* getUpperRight() { return &ptUpperRight; }

   // Update the LM's position with the given user interface and time interval
   void updateLM(const Interface* pUI) { lm.update(pUI, TIME_INTERVAL); }

   // Get the position of the Lunar Module
   Point* getLMPos() { return lm.getPos(); }

   // Get the velocity of the Lunar Module
   double getLMVel() { return lm.getVel(); }

   // Get the angle of the Lunar Module
   Angle* getLMAngle() { return lm.getAngle(); }

   // Get the fuel level of the Lunar Module
   int getLMFuel() { return lm.getFuel(); }

   // Get the altitude of the Lunar Module above the ground
   double getLMAltitude() { return ground.getElevation(*(lm.getPos())); }

   // Get if the LM thruster is on
   bool getLMThrust() { return lm.getThrust(); }

   // Get if the LM is rotating left
   bool getLMRotateLeft() { return lm.getRotateLeft(); }

   // Get if the LM is rotating right
   bool getLMRotateRight() { return lm.getRotateRight(); }

   // Get the list of stars
   list<Star*>* getStars() { return &stars; }

   // Draw the ground
   const void drawGround(ogstream &out) { ground.draw(out); }

   // Returns if the Lander has hit the ground (or is below the ground)
   const bool hitGround() { return 0 > ground.getElevation(*(lm.getPos())); }

   // Checks if the Lander has landed safely on the platform
   const bool safelyLanded();

private:
   Point ptUpperRight;     // The upper right corner of the screen
   Lander lm;              // The Lunar Module
   list<Star*> stars;      // A list for all the Star pointers
   Ground ground;          // The ground

   // Create stars and add them to the list
   void createStars();
};