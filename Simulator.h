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
const int NUM_LANDERS = 10;      // The number of Landers

/*************************************************************************
 * Simulator
 * Represents a simulation environment, including ground, stars, and a lunar module.
 *************************************************************************/
class Simulator
{
public:
    // Constructor to initialize the different parts of the simulator with the upper 
    // right point and to create a list of stars.
   Simulator(const Point& ptUpperRight) : ptUpperRight(ptUpperRight), ground(ptUpperRight) {
      createStars(); // Create all the Stars to be displayed
   }

   // Get the upper right point of the simulator
   Point* getUpperRight() { return &ptUpperRight; }

   // Update the LM's position with the given user interface and time interval
   void updateLM(const Interface* pUI) {
       for (int i = 0; i < NUM_LANDERS; i++) {
           landers[i]->update(pUI, TIME_INTERVAL);
       }
   }

   int getNumLanders() { return NUM_LANDERS; }

   // Get the position of the Lunar Module
   Point* getLMPos(int index) { return landers[index]->getPos(); }

   // Get the velocity of the Lunar Module
   double getLMVel(int index) { return landers[index]->getVel(); }

   // Get the angle of the Lunar Module
   Angle* getLMAngle(int index) { return landers[index]->getAngle(); }

   // Get the fuel level of the Lunar Module
   int getLMFuel(int index) { return landers[index]->getFuel(); }

   // Get the altitude of the Lunar Module above the ground
   double getLMAltitude(int index) { return ground.getElevation(*(landers[index]->getPos())); }

   // Get if the LM thruster is on
   bool getLMThrust(int index) { return landers[index]->getThrust(); }

   // Get if the LM is rotating left
   bool getLMRotateLeft(int index) { return landers[index]->getRotateLeft(); }

   // Get if the LM is rotating right
   bool getLMRotateRight(int index) { return landers[index]->getRotateRight(); }

   // Get the list of stars
   list<Star*>* getStars() { return &stars; }

   // Draw the ground
   const void drawGround(ogstream &out) { ground.draw(out); }

   // Returns if the Lander has hit the ground (or is below the ground)
   const bool hitGround(int index) { return 0 > ground.getElevation(*(landers[index]->getPos())); }

   // Checks if the Lander has landed safely on the platform
   const bool safelyLanded(int index);

private:
   Point ptUpperRight;     // The upper right corner of the screen
   Lander* landers[NUM_LANDERS] = {new Lander(Point((ptUpperRight.getX()) - 20.0, ptUpperRight.getY() - 20.0)),
                                    new Lander(Point((ptUpperRight.getX()) - 50.0, ptUpperRight.getY() - 20.0)), 
                                    new Lander(Point((ptUpperRight.getX()) - 150.0, ptUpperRight.getY() - 20.0)), 
                                    new Lander(Point((ptUpperRight.getX()) - 200.0, ptUpperRight.getY() - 20.0)), 
                                    new Lander(Point((ptUpperRight.getX()) - 250.0, ptUpperRight.getY() - 20.0)), 
                                    (Lander*) (new LanderWASD(Point((ptUpperRight.getX()) - 100.0, ptUpperRight.getY() - 20.0))),
                                    (Lander*)(new LanderWASD(Point((ptUpperRight.getX()) - 75.0, ptUpperRight.getY() - 50.0))), 
                                    (Lander*)(new LanderWASD(Point((ptUpperRight.getX()) - 175.0, ptUpperRight.getY() - 50.0))), 
                                    (Lander*)(new LanderWASD(Point((ptUpperRight.getX()) - 175.0, ptUpperRight.getY() - 50.0))), 
                                    (Lander*)(new LanderWASD(Point((ptUpperRight.getX()) - 275.0, ptUpperRight.getY() - 50.0)))
   
   
   }; // The Landers
   list<Star*> stars;      // A list for all the Star pointers
   Ground ground;          // The ground

   // Create stars and add them to the list
   void createStars();
};