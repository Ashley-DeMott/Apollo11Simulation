#pragma once
// Objects within the Simulation
#include "ground.h"
#include "Star.h"
#include "Lander.h"

// List for Stars
#include <list>

using namespace std;

const int NUM_STARS = 50;  // The number of Stars to create

/*************************************************************************
 * Simulator
 * 
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Point& ptUpperRight) : ptUpperRight(ptUpperRight), ground(ptUpperRight), lm(Point((ptUpperRight.getX() / 2.0), ptUpperRight.getY() / 2.0)) {
      createStars();
   }

   Point* getUpperRight() {
      return &ptUpperRight;
   }

   void moveLM(double x, double y) {
      this->lm.addPos(x, y);
   }

   Point* getLMPos() {
      return lm.getPos();
   }

   double getLMVel() {
      return lm.getVel();
   }

   double getLMAngle() {
      return lm.getAngle();
   }

   int getLMFuel() {
      return lm.getFuel();
   }

   double getLMAltitude() {
      return ground.getElevation(*(lm.getPos()));
   }

   list<Star*>* getStars() {
      return &stars;
   }

   const void drawGround(ogstream &out) {
      ground.draw(out);
   }

private:
   Point ptUpperRight;     // The upper right corner of the screen
   Lander lm;              // The Lunar Module
   list<Star*> stars;      // A list for all the Star pointers
   Ground ground;          // The ground

   void createStars() {
      // For every star, generate a random X and Y position
      for (int i = 0; i < NUM_STARS; i++) {
         double posX = random(0.0, ptUpperRight.getX());
         double posY = random(0.0, ptUpperRight.getY());
         
         stars.push_back(new Star(Point(posX, posY)));
      }
      assert(stars.size() == NUM_STARS); // Make sure it generates all 50 stars
   }
};