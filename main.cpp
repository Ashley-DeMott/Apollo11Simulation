/*************************************************************
 * 1. Name:
 *      Ashley DeMott and Jason Geppelt
 * 2. Assignment Name:
 *      Lab 04: Apollo 11 Visuals
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      At first, the program was creating 50 new stars every time it
 *      looped through the callback. It was neat, but definetly not what
 *      we needed to do. Eventually we put all the stars in a list before 
 *      the callback loop and then during the loop, updated each star's 
 *      phase.       
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

   // Update the Lunar Lander
   sim->updateLM(pUI);

   // draw our little stars (behind the ground)
   for (Star* s : *(sim->getStars())) {
      // Extra: random stars
      //gout.drawStar(Point( random(0.0, sim->getUpperRight()->getX()), random(0.0, sim->getUpperRight()->getY())), random(0, 255));
      gout.drawStar(*(s->getPos()), s->getPhase());
   }
   
   // draw the ground
   sim->drawGround(gout);

   // draw the lander and its flames
   gout.drawLander(*(sim->getLMPos()) /*position*/, sim->getLMAngle()->getRadians() /*angle*/);
   gout.drawLanderFlames(*(sim->getLMPos()), sim->getLMAngle()->getRadians(), /*angle*/
                    pUI->isUp(), pUI->isLeft(), pUI->isRight());

   // Printing near the top left of the screen,   
   gout.setPosition(Point(10.0, sim->getUpperRight()->getY() - 20.0));

   // Show the Lunar Modules Fuel level
   gout << "Fuel: " << sim->getLMFuel() << "\n";
   
   // Only show the Altitude and Speed with 2 decimal points
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(2);
   gout << "Altitude: " << sim->getLMAltitude() << " meters\n";
   gout << "Speed: " << sim->getLMVel() << "m/s\n";
   //gout << "Angle: " << sim->getLMAngle()->getDegrees() << " degrees\n";
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