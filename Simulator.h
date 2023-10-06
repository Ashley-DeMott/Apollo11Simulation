#pragma once
// Objects within the Simulation
#include "ground.h"
#include "Star.h"
#include "Lander.h"

// List for Stars
#include <list>

using namespace std;

const int NUM_STARS = 50;  // The number of Stars to create
#define TIME_INTERVAL 0.1 // How often callBack is called, the speed of the Simulation

/*************************************************************************
 * Simulator
 * Represents a simulation environment, including ground, stars, and a lunar module.
 *************************************************************************/
class Simulator
{
public:
    // Constructor to initialize the different parts of the simulator with the upper 
    // right point and to create a list of stars.
   Simulator(const Point& ptUpperRight) : ptUpperRight(ptUpperRight), ground(ptUpperRight), lm(Point((ptUpperRight.getX() / 2.0), ptUpperRight.getY() / 2.0)) {
      createStars(); // Create all the Stars to be displayed
   }

   // Get the upper right point of the simulator
   Point* getUpperRight() {
      return &ptUpperRight;
   }

   // Update the LM's position with the given user interface and time interval
   void updateLM(const Interface *pUI) {
      lm.update(pUI, TIME_INTERVAL);
   }

   // Get the position of the Lunar Module
   Point* getLMPos() {
      return lm.getPos();
   }

   // Get the velocity of the Lunar Module
   double getLMVel() {
      return lm.getVel();
   }

   // Get the angle of the Lunar Module
   Angle* getLMAngle() {
      return lm.getAngle();
   }

   // Get the fuel level of the Lunar Module
   int getLMFuel() {
      return lm.getFuel();
   }

   // Get the altitude of the Lunar Module above the ground
   double getLMAltitude() {
      return ground.getElevation(*(lm.getPos()));
   }

   // Get the list of stars
   list<Star*>* getStars() {
      return &stars;
   }

   // Draw the ground
   const void drawGround(ogstream &out) {
      ground.draw(out);
   }

private:
   Point ptUpperRight;     // The upper right corner of the screen
   Lander lm;              // The Lunar Module
   list<Star*> stars;      // A list for all the Star pointers
   Ground ground;          // The ground

   // Create stars and add them to the list
   void createStars() {
      // For every star, generate a random X and Y position
      for (int i = 0; i < NUM_STARS; i++) {
         double posX = random(0.0, ptUpperRight.getX());
         double posY = random(0.0, ptUpperRight.getY());
         
         // Add the new Star to the list of Stars
         stars.push_back(new Star(Point(posX, posY)));
      }
      assert(stars.size() == NUM_STARS); // Make sure it generates all 50 stars
   }
};