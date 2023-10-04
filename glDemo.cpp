/*************************************************************
 * 1. Name:
 *      Ashley DeMott and Jason Geppelt
 * 2. Assignment Name:
 *      Lab 04: Apollo 11 Visuals
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      so far 2ish hrs
 *****************************************************************/
#include "Simulator.h"
#include "uiInteract.h"
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
   Simulation* sim = (Simulation *)p;

   // move the ship around
   if (pUI->isRight())
      sim->moveLM(1.0, 0.0);
   if (pUI->isLeft())
      sim->moveLM(-1.0, 0.0);
   if (pUI->isUp())
      sim->moveLM(0.0, 1.0);
   if (pUI->isDown())
      sim->moveLM(0.0, -1.0);

   // draw the ground
   sim->ground.draw(gout);

   // draw the lander and its flames
   gout.drawLander(*(sim->getLMPos()) /*position*/, sim->angle /*angle*/);
   gout.drawLanderFlames(*(sim->getLMPos()), sim->angle, /*angle*/
                    pUI->isDown(), pUI->isLeft(), pUI->isRight());

   // put some text on the screen
   gout.setPosition(Point(1.0, 3.0));
   gout << "Position (" << (int)sim->getLMPos()->getX() << ", " << (int)sim->getLMPos()->getY() << ")" << "\n";

   // draw our little star
   gout.drawStar(sim->ptStar, sim->phase++);
   // start-tick - clock() <-- # ticks per call
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
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
   Simulation demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);

   return 0;
}