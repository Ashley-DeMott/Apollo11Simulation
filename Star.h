#pragma once
#include "point.h"
const int MAX_PHASE = 255; // Maximum phase value for the star

/*********************************
 * STAR
 * The decorative star in space, keeping track of its position and phase.
 *********************************/
class Star {
public:
    // Constructor to initialize a Star with a given position and a random phase
    Star(Point p = Point(0.0, 0.0)) : pos(p.getX(), p.getY()), phase(random(0, MAX_PHASE)) {}

    // Get the position of the star
    Point* getPos() { return &pos; }

    // Get the current phase of the star and update it
    int getPhase() {
        updatePhase();
        return phase;
    }

    // Increment the Star's phase (up to 255, then resets to 0)
    void updatePhase() { phase = (phase < MAX_PHASE) ? phase++ : 0; }

private:
    Point pos;  // The position of the star
    int phase;  // The phase of the star, controlling its appearance
};