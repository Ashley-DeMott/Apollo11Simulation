/*************************************************************
 * 1. Name:
 *      Ashley DeMott and Jason Geppelt
 * 2. Assignment Name:
 *      Lab 05: Apollo 11 Code Complete
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *     At first, the Lander wasn't being registered as "on the platform" since
 *      Ground::onPlatform checked if the Lander was between 1.0 and 0.0 meters.
 *      The Lander would sometimes be at a negative altitude, but still within
 *      the +/-1.0 meter of the correct altitude, and that approximate range
 *      is needed when working with doubles/floating point values.
 *    Also, the Lander's thrusters would still be drawn as "on" even if the
 *      Lander was out of fuel, or had landed. We fixed this by keeping 
 *      all user input within the Lander class, and drawLanderFlames now
 *      has to ask the Simulator which of the Lander's thursters are on.
 * 5. How long did it take for you to complete the assignment?
 *     5 hrs
 *****************************************************************/
#include "Simulator.h"
#include "uiDraw.h"

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void * p)
{
   ogstream gout;

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* sim = (Simulator *)p;

   // Update the Lunar Lander (will do nothing if the Lunar has hit the ground)
   sim->updateLM(pUI);

   // If the Lander has hit the ground,
   if (sim->hitGround()) {
       // Print end-of-game message
       gout.setPosition(Point(sim->getUpperRight()->getX() - 250.0, sim->getUpperRight()->getY() - 125.0));
       
       // If the Lander has safely landed,
       if (sim->safelyLanded()) {
           gout << "The Eagle has landed!"; 
       }
       // The Lander is not travelling at a safe velocity or is not on the platform,
       else {
           gout << "Houston, we have a problem!";
       }
   }
   
   // DRAWING //

   // draw our little stars (behind the ground)
   for (Star* s : *(sim->getStars())) {
       gout.drawStar(*(s->getPos()), s->getPhase());
   }

   // draw the ground
   sim->drawGround(gout);

   // Draw the lander and its flames
   gout.drawLander(*(sim->getLMPos()) /*position*/, sim->getLMAngle()->getRadians() /*angle*/);
   gout.drawLanderFlames(*(sim->getLMPos()), sim->getLMAngle()->getRadians(), /*angle*/
                    sim->getLMThrust(), sim->getLMRotateLeft(), sim->getLMRotateRight());

   // Print messages to the screen
   // Printing near the top left of the screen,
   gout.setPosition(Point(10.0, sim->getUpperRight()->getY() - 20.0));

   // Show the Lunar Modules Fuel level
   gout << "Fuel: " << sim->getLMFuel() << " lbs\n";
   
   // Displays the altitute as 0 or the actual altitude (prevents negative altitude from showing)
   gout.setf(ios::fixed); 
   gout.precision(0);
   gout << "Altitude: " << max(0.0, sim->getLMAltitude()) << " meters\n";
   
   // Show the Speed with 2 decimal points
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(2);
   gout << "Speed: " << sim->getLMVel() << "m/s\n";
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * the simulator and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance, 
   _In_opt_ HINSTANCE hPrevInstance, 
   _In_ PWSTR pCmdLine, 
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char ** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Point ptUpperRight(400.0, 400.0);
   Interface ui(0, NULL, 
                "Lunar Module - CSE230 Team 2", 
                 ptUpperRight);

   // Initialize the game class
   Simulator sim(ptUpperRight);

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}